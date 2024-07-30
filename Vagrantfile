Vagrant.configure("2") do |config|
  config.vm.box = "envimation/ubuntu-xenial-docker"
  config.vm.network "public_network", bridge: 'en0: Wi-Fi (AirPort)'
  config.vm.provision "shell", inline: <<-SHELL
  sudo apt-get update
  sudo apt-get install vim -y
  sudo apt-get install net-tools -y
  sudo apt-get install ansible -y
SHELL
end
