#!/bin/bash
#Program: moniter user of quota.
#History: 19/5/1 gorkr
#Usage:
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH


user=`/usr/sbin/repquota -u /storage/user/ | tail -n +7 | awk -F ' ' '{print $1}'`  # all of users wrote in quota, excipt root

for i in $user  # $user和${user}一样吗
    do
        used=`/usr/sbin/repquota -u /storage/user/ | grep $i | awk -F " " '{print $3}'`
        limit=`/usr/sbin/repquota -u /storage/user/ | grep $i | awk -F " " '{print $5}'`
        if [ $used -ge $limit ];then  #  这里是 是否大于指定大小
            echo "$user had overflow"
	    date=`date +%Y%m%d`
            tar -czvf /storage/safeplace/${i}-${date}.tar.gz /storage/user/home/${i}/  # 将制定路径打包， 将其存放在指定目录

            rm -rf /storage/user/home/${i}/*  # 将文件删除
        fi
    done
