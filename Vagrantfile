#!/bin/bash
vagrant destroy
vagrant up --provider=virtualbox --provision
vagrant scp deploy.sh :/home/vagrant
vagrant scp $HOME/.ssh/id_rsa :/home/vagrant/.ssh/
vagrant scp $HOME/.ssh/id_rsa.pub :/home/vagrant/.ssh/
# pwd is vagrant
ssh vagrant@127.0.0.1 -p 2222
mickael@MacBook-Pro-de-Mickael ansible-playground % ls
Vagrantfile	deploy.sh	go_dc.sh
mickael@MacBook-Pro-de-Mickael ansible-playground % cat Vagrantfile
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
