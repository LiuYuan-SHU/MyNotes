from bs4 import BeautifulSoup

html = """
<html>
    <head>
        <title>The Document's story</title>
    </head>
    <body>
        <p class="story">
            Once upon a time there were three little sisters; and their names were
            <a href="http://example.com/elsie" class="sister" id="link1">
                <span>Elsie</span>
            </a>,
            <a href="http://example.com/lacie" class="sister" id="link2">Lacie</a>
            and
            <a href="http://example.com/tillie" class="sister" id="link3">Tillie</a>;
            and they lived at the bottom of a well.
        </p>
        <p clss="story">...</p>
"""
def contents():
    soup = BeautifulSoup(html, 'lxml')
    print(type(soup.p.contents))
    for item in soup.p.contents:
        print(str(item).strip())


def children():
    soup = BeautifulSoup(html, 'lxml')
    print(type(soup.p.children))
    for item in soup.p.children:
        print(str(item).strip())


def descendants():
    soup = BeautifulSoup(html, 'lxml')
    print(type(soup.p.descendants))
    # enumerate: 将一个可遍历对象转换为一个索引序列
    # 同时列出数据下标和数据
    for item, child in enumerate(soup.p.descendants):
        print(item, child)


contents()
children()
descendants()
