package main

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"strings"

	"github.com/gocolly/colly/v2"
)

func main() {
	// Create a new collector
	c := colly.NewCollector()

	// URL of the PKI server's CSR submission endpoint
	pkiURL := "https://pki-server.example.com/upload-csr"

	// The CSR file to be uploaded
	csrFile := "path/to/your.csr"

	// Open the CSR file
	file, err := os.Open(csrFile)
	if err != nil {
		log.Fatalf("Failed to open CSR file: %v", err)
	}
	defer file.Close()

	// Prepare the POST request
	c.OnRequest(func(r *colly.Request) {
		fmt.Println("Uploading CSR...")
	})

	// Handle the response after the CSR upload
	c.OnResponse(func(r *colly.Response) {
		if r.StatusCode == http.StatusOK {
			fmt.Println("CSR uploaded successfully!")
			// Process the form returned in the response
			submitCommonNameForm(r.Body)
		} else {
			fmt.Printf("Failed to upload CSR, Status Code: %d\n", r.StatusCode)
		}
	})

	// Use a request context to upload the CSR as multipart form-data
	err = c.PostMultipart(pkiURL, map[string][]byte{
		"csr": fileBytes(csrFile),
	})

	if err != nil {
		log.Fatalf("Failed to submit CSR: %v", err)
	}
}

// submitCommonNameForm handles the submission of the CommonName after CSR upload
func submitCommonNameForm(responseBody []byte) {
	// Create a new collector for submitting the CommonName form
	c := colly.NewCollector()

	// URL for submitting the CommonName (this URL might be the same or different depending on your PKI server)
	commonNameURL := "https://pki-server.example.com/submit-common-name"

	// Assuming the form contains a field named 'CommonName' that needs to be filled
	commonName := "example.com" // Set this to the desired CommonName value

	// Prepare the POST request for the CommonName submission
	c.OnRequest(func(r *colly.Request) {
		fmt.Println("Submitting CommonName...")
	})

	// Handle the response after CommonName submission
	c.OnResponse(func(r *colly.Response) {
		if r.StatusCode == http.StatusOK {
			fmt.Println("CommonName submitted successfully!")
		} else {
			fmt.Printf("Failed to submit CommonName, Status Code: %d\n", r.StatusCode)
		}
	})

	// Extract form data from the response (this is a simple approach; adjust based on actual response structure)
	formData := make(map[string]string)
	formData["CommonName"] = commonName

	// Perform a POST request to submit the CommonName
	err := c.Post(commonNameURL, formData)
	if err != nil {
		log.Fatalf("Failed to submit CommonName: %v", err)
	}
}

// fileBytes reads the content of a file and returns it as a byte slice
func fileBytes(filepath string) []byte {
	file, err := os.ReadFile(filepath)
	if err != nil {
		log.Fatalf("Failed to read file: %v", err)
	}
	return file
}
