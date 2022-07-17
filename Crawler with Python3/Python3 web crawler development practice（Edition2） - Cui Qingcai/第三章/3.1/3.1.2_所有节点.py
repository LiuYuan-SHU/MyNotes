from lxml import etree


def get_all_nodes():
    html = etree.parse('./test.html', etree.HTMLParser())
    result = html.xpath('//*')
    print(result)


def get_li_nodes():
    html = etree.parse('./test.html', etree.HTMLParser())
    result = html.xpath('//li')
    print(result)

# get_all_nodes()
get_li_nodes()