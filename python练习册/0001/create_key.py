#!/usr/bin/env python3
#coding = utf-8

#第 0001 题：做为 Apple Store App 独立开发者，你要搞限时促销，为你的应用生成激活码（或者优惠券），
#使用 Python 如何生成 200 个激活码（或者优惠券）？

import random
import string

def create_key(num, group = 4):
    """return a file with secret key

    group -- the number of consisting parts. 'XaD1-SDA1-3S4S', group = 3.
    num -- the number of keys.
    """

    field = string.ascii_letters + string.digits  #[A-Za-z0-9]

    with open("secret_key.txt", "w") as f:
        for i in range(num):
            key ='-'.join(
                          [''.join(random.sample(field, 4))  #a string, like 'XaD1'
                          #>>>random.sample('abcdefghij', 3)
                          # ['a', 'd', 'b']
                          for _ in range(group)]  #creat string groupth.
                          )  #a string for secret_key
            f.write(key+'\n')

if __name__ == "__main__":
    create_key(200)

#string模块参考
#https://docs.python.org/3/library/string.html
#
#random模块参考
#https://www.cnblogs.com/dylancao/p/8079230.html
#
#使用命令执行python文件
#https://www.cnblogs.com/HeDaoYiWenZi/articles/2855965.html
#
#linux 命令执行
#$chmod u+x create_key.py
