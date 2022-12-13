#!/bin/bash -ev

mkdir -p ~/.pozoqo
echo "rpcuser=username" >>~/.pozoqo/pozoqo.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.pozoqo/pozoqo.conf

