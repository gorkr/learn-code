#!/usr/bin/env python3
#coding = utf-8

import re

#第 0004 题： 任一个英文的纯文本文件，统计其中的单词出现的个数。
#english_file_path = './word.txt'

def get_words(file):
    """get the of number of words in file.

    Args:
        file: the path of english file.

    Return:
        a int value.
    """

    pattern = re.compile(r"[a-zA-Z]+(\n| )")   #waht's 这种情况

    with open(file, 'r') as f:
        article = f.read()
        words_list = re.findall(r"[a-zA-Z0-9]+", article)
        num = len(words_list)

    return num

if __name__ == "__main__":
    print(get_words('test.txt'))
