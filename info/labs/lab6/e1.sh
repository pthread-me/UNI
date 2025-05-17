#!/bin/zsh

openssl genpkey -paramfile dhp.pem -out private_key.pem
openssl pkey -in private_key.pem -pubout -out public_key.pem
openssl pkeyutl -derive -inkey private_key.pem -peerkey TA_key.pem -out shared_secret.bin
echo "Secret code" > message.txt
openssl enc -aes-256-cbc -pbkdf2 -in message.txt -out message.enc -pass file:shared_secret.bin
openssl enc -aes-256-cbc -d -pbkdf2 -in message.enc -out message.dec -pass file:shared_secret.bin
diff message.txt message.dec
cat message.dec

