from lxml import etree


def wrong_select():
    html = etree.parse('./test.html', etree.HTMLParser())
    result1 = html.xpath('//li[@class="item-0"]/text()')
    result2 = html.xpath('//li[@class="item-0"]')
    print(result1)
    print(result2)


def select_with_level():
    html = etree.parse('./test.html', etree.HTMLParser())
    result = html.xpath('//li[@class="item-0"]/a/text()')
    print(result)


def select_with_double_slash():
    html = etree.parse('./test.html', etree.HTMLParser())
    result = html.xpath('//li[@class="item-0"]//text()')
    print(result)


# wrong_select
select_with_level()
select_with_double_slash()