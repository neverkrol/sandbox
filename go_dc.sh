#!/bin/bash
vagrant destroy
vagrant up --provider=virtualbox --provision
vagrant scp deploy.sh :/home/vagrant
vagrant scp $HOME/.ssh/id_rsa :/home/vagrant/.ssh/
vagrant scp $HOME/.ssh/id_rsa.pub :/home/vagrant/.ssh/
# pwd is vagrant
ssh vagrant@127.0.0.1 -p 2222
