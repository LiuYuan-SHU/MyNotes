from lxml import etree

html = etree.parse('./test.html', etree.HTMLParser())
result = html.xpath('//a[@href="link4.html"]/../@class')
print(result)
result = html.xpath('//a[@href="link4.html"]/parent::*/@class')
print(result)