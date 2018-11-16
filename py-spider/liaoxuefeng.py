# coding = utf-8

#應該是 封ip
from __future__ import unicode_literals

import logging
import os
import re
import time

from urllib.parse import urlparse  #urlparese()实现URL的识别和分段

import requests
from bs4 import BeautifulSoup
import pdfkit

html_template = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
</head>
<body>
{content}
</body>
</html>
"""


class Crawler(object):
    """
    爬虫基类，所有爬虫都应该继承此类
    """
    name = None

    def __init__(self, name, start_url):
        """
        初始化
        :param name: 将要被保存为PDF的文件名称
        :param start_url: 爬虫入口URL
        """
        self.name = name
        self.start_url = start_url
        self.domain = '{uri.scheme}://{uri.netloc}'.format(uri=urlparse(self.start_url))
        # uri 是一个ParseResult对象, scheme 代表协议部分,  netloc返回域名部分

    @staticmethod  #静态方法装饰器, 相当于 request = staticmethod(request)
    def request(url):
        # 静态方法不需要self参数, 作用于类, 通过类来调用. 如: Crawler.request()
        """
        网络请求,返回response对象
        :return:
        """
        headers = {
            'User-Agent': 'Mozilla/5.0(Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/537.36(KHTML, like Gecko) Chrome/65.0.3325.162 Safari/537.36'
        }

        response = requests.get(url, headers=headers)
        print(response.status_code)
        while(200!=response.status_code):
            response = requests.get(url, headers=headers)
            print(response.status_code)
        return response

    def parse_menu(self, response):
        """
        解析目录,由子类实现
        从response中解析出所有目录的URL链接
        """
        raise NotImplementedError

    def parse_body(self, response):
        """
        解析正文,由子类实现
        :param response: 爬虫返回的response对象
        :return: 返回经过处理的html正文文本
        """
        raise NotImplementedError

    def run(self):
        start = time.time() #获取当前时间
        options = {
            'page-size': 'Letter',
            'margin-top': '0.75in',
            'margin-right': '0.75in',
            'margin-bottom': '0.75in',
            'margin-left': '0.75in',
            'encoding': "UTF-8",
            'custom-header': [
                ('Accept-Encoding', 'gzip')
            ],
            'cookie': [
                ('cookie-name1', 'cookie-value1'),
                ('cookie-name2', 'cookie-value2'),
            ],
            'outline-depth': 10,
        }
        htmls = []
        for index, url in enumerate(self.parse_menu(self.request(self.start_url))): #enumerate() 参数是列表, 迭代 索引-值 对儿.
            print(url)
            html = self.parse_body(self.request(url))
            f_name = ".".join([str(index), "html"])
            with open(f_name, 'wb') as f:
                f.write(html)
            htmls.append(f_name)
        #for html in htmls:
        pdfkit.from_file(htmls, self.name + ".pdf", options=options)
        #for html in htmls:
            #s.remove(html)  #os.remove(path) 删除指定文件
        total_time = time.time() - start
        print(u"总共耗时：%f 秒" % total_time)


class LiaoxuefengPythonCrawler(Crawler):
    """
    廖雪峰Python3教程
    """

    def parse_menu(self, response):
        """
        解析目录结构,获取所有URL目录列表
        :param response 爬虫返回的response对象
        :return: url生成器
        """
        soup = BeautifulSoup(response.content, "html.parser")
        menu_tag = soup.find_all(class_="uk-nav uk-nav-side")[1]
        for li in menu_tag.find_all("div"):
            url = li.a.get("href")
            if not url.startswith("https"):
                url = "".join([self.domain, url])  # 补全为全路径
            yield url  #yield 的用法


    def parse_body(self, response):
        """
        解析正文
        :param response: 爬虫返回的response对象
        :return: 返回处理后的html文本
        """
        try:
            soup = BeautifulSoup(response.content, 'html.parser')
            body = soup.find_all(class_="x-wiki-content")[0]

            # 加入标题, 居中显示
            title = soup.find('h4').get_text()
            center_tag = soup.new_tag("center")
            title_tag = soup.new_tag('h1')
            title_tag.string = title
            center_tag.insert(1, title_tag)
            body.insert(1, center_tag)

            html = str(body)
            # body中的img标签的src相对路径的改成绝对路径
            pattern = "(<img .*?src=\")(.*?)(\")"

            def func(m):
                if not m.group(2).startswith("http"):
                    rtn = "".join([m.group(1), self.domain, m.group(2), m.group(3)])
                    return rtn
                else:
                    return "".join([m.group(1), m.group(2), m.group(3)])

            html = re.compile(pattern).sub(func, html)
            html = html_template.format(content=html)
            html = html.encode("utf-8")
            return html
        except Exception as e:
            logging.error("解析错误", exc_info=True)


if __name__ == '__main__':
    start_url = "https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000"
    crawler = LiaoxuefengPythonCrawler("廖雪峰Git", start_url)
    crawler.run()



'''s



def parse_url_html(url):
    reponse = requests.get(url)
    soup = BeautifulSoup(reponse.content, "html.parser")
    body = soup.find(class_="x-wiki-content")[0]
    html = str(body)
    with open("a.html", 'wb') as f:
        f.write(html)

def get_url_list():
    reponse = requests.get("https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000")
    soup = BeautifulSoup(reponse.content, "html.parser")
    menu_tag = soup.fing_all(class_="uk-nav uk-nav-side")[1]
    urls = []
    for li in menu_tag.find_all("div"):
        url = "http://www.liaoxuefeng.com" + li.a.get('href')
        urls.append(url)
    return urls

def save_pdf(htmls):
    options = {
        'page-size': 'Letter',
        'encoding': 'UTF-8',
        'custom-header': [
            ('Accept-Encoding', 'gzip')
        ]
    }

    pdfkit.from_file(htmls, file_name, options=options)
'''
