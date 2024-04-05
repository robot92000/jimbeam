#!/bin/bash
# This requres wireguard and wireguard-tools

wg genkey | tee privatekey | wg pubkey > publickey
#command used from Wireguard's setup documentation, creats two files with each key

privkey="$(cat privatekey)"
pblkey="$(cat publickey)"
#put the keys into varibles

echo Generating Wireguard Key Pair... $'\n'
echo "Private Key: $privkey"
echo "Public Key:  $pblkey" $'\n'
#display keys on output

basename="Wireguard-Key-Pair-"
date=$(date +"%Y-%m-%d_%H-%M-%S")
extension=".txt"
filename="$basename$date$extension"
#create file name format with date and time

touch $filename
echo "Private Key: $privkey" > $filename 
echo "Public Key:  $pblkey" >> $filename
#create file and append keys

echo Key pair saved to: $filename

rm privatekey && rm publickey
