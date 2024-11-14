#!/bin/bash
if [ "$1" != "" ]; then
	hostname=$1
	
	# Check if device is online
	timeout=2
	ping $hostname -c 1 -W $timeout > /dev/null
	if [ $? == 0 ]; then		
		echo ">>Copying files to root@$hostname"
		ssh root@$hostname 'mkdir -p /home/opi/scripts'
		scp base_baro.sh root@$hostname:/home/opi/scripts/
		scp base_baro.service root@$hostname:/etc/systemd/system/
		
		echo ">>Done."
	else
		echo "$hostname is offline :("
	fi
else
	echo "Usage: copyCodeToPi.sh [hostname]"
fi
