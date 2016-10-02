#!/usr/bin/env bash
# taocp_1.2.1_P_verify.sh - used to verify output is correct of taocp_1.2.1_P.c (or any equation seperated by '=')
# This program is part of the public domain - Kenneth B. Jensen, 2016 <kenneth@jensen.cf>
# Arguments are a logfile, accepts input from stdin

IFS=$'\n'
file="${1:-/dev/stdin}"
while read x; do
	left=$(bc <<< `sed 's/=.*//' <<< $x`)
	right=$(bc <<< `sed 's/.*=//' <<< $x`)
	printf "%d = %d: " $left $right 
	[[ $left -eq $right ]] && echo "true" || echo "false"
done < $file
