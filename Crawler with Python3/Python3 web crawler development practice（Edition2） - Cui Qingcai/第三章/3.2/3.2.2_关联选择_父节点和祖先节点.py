from bs4 import BeautifulSoup

html = """
<html>
    <head>
        <title>The Dormouse's story<title>
    </head>
    <body>
        <p class="story">
            Once upon a time where were three little sisters; and their names were
            <a href="http://example.com/elsie" clsss="sister" id="link1">
                <span>Elsie</span>
            </a>
        </p>
        <p class="story">...</p>
"""


def parent():
    soup = BeautifulSoup(html, 'lxml')
    print(soup.a.parent)


def parents():
    soup = BeautifulSoup(html, "lxml")
    for item, element in enumerate(soup.a.parents):
        print(item, element)


# parent()
parents()