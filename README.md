create an ubuntu box using vagrant (./go_dc.sh) and login in it, just enter vagrant password
./deploy.sh --create-debian x will create x debian boxes and start them
./deploy.sh --ansible will create the ansible config for these debian boxes
cd ansible_dir
ansible -i ... -m ping all 

this can be used as a lab for ansible activities
