#! /bin/bash

function get_user_home
{
	grep "$1" /etc/passwd | cut -d':' -f6
}

USERDIR=$(get_user_home $USERNAME)

if [ -z "$1" ]; then
	echo "Usage: $0 username"
	exit 1
fi

USERDIR=$(get_user_home $1)

if [ -n "SUSEDIR" ]; then
	echo SUSEDIR
fi


