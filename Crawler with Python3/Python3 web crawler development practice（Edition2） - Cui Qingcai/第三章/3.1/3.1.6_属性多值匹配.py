from lxml import etree

text = '''
<li class="li li-first">
    <a href="link.html">
        first item
    </a>
</li>
'''

html = etree.HTML(text)
result = html.xpath('//li[@href="li"]')
print(result)

result = html.xpath('//li[contains(@class, "li")]')
print(result)
