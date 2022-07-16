from requests import get
import re                   # 正则表达式库

def get_test():
    data = {
        'name': 'germey',
        'age': 25
    }
    r = get('https://www.httpbin.org/get', params=data)
    print(r.text)

def get_json():
    r = get('https://www.httpbin.org/get')
    print(r.text)
    print(r.json())
    print(type(r.json()))

def get_web():
    r = get('https://ssr1.scrape.center/')
    pattern = re.compile('<h2.*?>(.*?)</h2>', re.S)
    titles = re.findall(pattern, r.text)
    print(titles)

def get_binary():
    r = get('https://scrape.center/favicon.ico')
    with open('favicon.ico', 'wb') as f:
        f.write(r.content)

def add_headers():
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) '
                      'Chrome/52.0.2743.116 Safari/    537.36 '
    }
    response = get('https://ssr1.scrape.center/', headers=headers)
    print(response.text)

# get_test()
# get_json()
# get_web()
# get_binary()
add_headers()