#!/usr/bin/env python3
#coding = utf-8

#第 0002 题: 将 0001 题生成的 200 个激活码（或者优惠券）保存到 MySQL 关系型数据库中。
#思路; 将保存好的文本再转存进入mysql

#import sys
#sys.path.append("../0001/")
#from create_key import create_key
#create_key(10)


import pymysql

# 连接数据库
db = pymysql.connect(host='localhost',
                     user='root',
                     password='zxy123',
                     db='SECERET',
                     charset='utf8')

try:
    with db.cursor() as cursor:  #创建游标对象
        create_table = """CREATE TABLE seceret_key (
                              key_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
                              key_value VARCHAR(20)
                            )""" #用于mysql创建表的字符串
        insert = "INSERT INTO `seceret_key` ( `key_value`) VALUES (%s)"

        cursor.execute("DROP TABLE IF EXISTS seceret_key")  #如果该表已存在,则删除
        cursor.execute(create_table)  #建表

        # 打开上个联系中保存好秘钥的文本文件
        with open("../0001/secret_key.txt", "r") as f:
            cursor.executemany(insert, f.readlines())

    # connection is not autocommit by default.
    # So you must commit to saveyour changes.
    db.commit()
finally:
    db.close()



#但会有表对象

#使用path导入不同层级的py文件
#https://blog.csdn.net/lwgkzl/article/details/81161985
#https://blog.csdn.net/qq_28072715/article/details/80939699
#
#pymysql官方文档
#https://pymysql.readthedocs.io/en/latest/user/index.html

#linux 命令执行
#$chmod u+x save_mysql.py
