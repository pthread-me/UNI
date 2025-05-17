#!/bin/zsh

openssl req -nodes -new -x509 -keyout private_key.pem -out domain.crt \
											-subj "/C=CA/ST=NS/L=Halifax/O=Anas/CN=Lab6"
