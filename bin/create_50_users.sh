#!/bin/bash
#Shell name:create_50_users.sh
#Program:
#    create 50 users in a dirctory
#History:
#    2019/5/1 gorkr
#
#
#Usage:
#    chmod 700 create_50_users.sh
#    sudo ./create_50_users.sh
#

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

if [ $UID -ne 0 ]
then
  echo "Run as root"
  exit 1
fi

sb=400M  # 400M softblock
hb=500M  # 500M hardblock
gr=432000  # 5 days grace

for i in `seq 50`
do
  useradd -G test test$i -d /storage/user/test/home/test$i -m  >/dev/null 2>/dev/null
  setquota -u test$i ${sb} ${hb} 0 0 /storage/user/
  if [ $i -lt 46 ]
  then
    dd if=/dev/zero of=/storage/user/test/home/test$i/file bs=2k count=1
  elif [ $i -lt 48 ]
  then
    dd if=/dev/zero of=/storage/user/test/home/test$i/file bs=1M count=250
  else
    dd if=/dev/zero of=/storage/user/test/home/test$i/file bs=1M count=550
  fi
  chown test$i:test$i /storage/user/test/home/test$i/file
  [ $? -eq 0 ] && echo -e "[\033[32mok\033[0m]user test$i create success."
done
exit 0
