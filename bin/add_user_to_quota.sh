#!/bin/bash
#Shell name:add_user_to_quota.sh
#Program:
#    add a user to quota,with 400M soft, 500M hard, grace 5.
#History:
#    2019/5/1 gorkr
#Usage:
#    source add_user_to_quota.sh username

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

sb=409600  # 400M softblock
hb=512000  # 500M hardblock
gr=432000  # 5 days grace

if [ $UID -ne 0 ]
then
  echo "Run as root"
  exit 1
fi

setquota -u $1 ${sb} ${hb} 0 0 /storage/user/ -t ${gr}
exit 0
