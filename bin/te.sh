#! /bin/bash

DDIR="/tmp"  #destination of directory

function does_user_exist
{
	grep "$1" /etc/passwd > /dev/null 2>&1
	return $?
}

function get_user_home
{
	grep "$1" /etc/passwd | cut -d':' -f6
}

if [ -n "$1" ]; then
	USERNAME=$1
else
	read -p "Enter the user name: "USERNAME""
fi

until does_user_exist $USERNAME; do
	read read -p "Enter thr user name:" USERNAME
done

USERDIR=$(get_user_home $USERNAME)

if [ -d "$USERDIR" ]; then # -d 检查是否是一个路径
	ARCHIVE="$USERNAME-`date +%d-%m-%Y`.tar.bz2"
	tar -cjf "$DDIR?$ARCHIVE" "@USERDIR"
else
	echo "This user doesn't have a valide home direcory"
	exit 1
fi

