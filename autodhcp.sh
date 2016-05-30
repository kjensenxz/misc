#!/bin/sh
# autodhcp.sh - begin dhcp on selected interface
# Kenneth Jensen <kenneth@jensen.cf>
# This software is in the public domain and is provided "as is" with no provided warranty. 

ifaces=$(ip a | egrep '^[0-9]+' | awk '{print $2}' | sed 's/:$//')
i=1
for iface in $ifaces; do
	echo "$i: $iface"
	let "i++"
done
unset i

printf "start dhcp on iface #: "
read input
selection=$(sed "$input!d" <<< "${ifaces}" )

printf "starting dhcpcd on iface %s\n" "$selection"
sudo dhcpcd "$selection"
