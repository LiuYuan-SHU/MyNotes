from http import cookiejar
from urllib import request

def get_cookie():
    cookie = cookiejar.CookieJar()
    handler = request.HTTPCookieProcessor(cookie)
    opener = request.build_opener(handler)
    response = opener.open('https://www.baidu.com')
    for item in cookie:
        print(item.name + " " + item.value)

def save_cookie_in_Mozilla():
    filename = 'cookie_Mozilla.txt'
    cookie = cookiejar.MozillaCookieJar(filename)
    handle = request.HTTPCookieProcessor(cookie)
    opener = request.build_opener(handle)
    response = opener.open('https://www.baidu.com')
    cookie.save(ignore_discard=True, ignore_expires=True)

def save_cookie_in_LWP():
    filename = 'cookie_LWP.txt'
    cookie = cookiejar.LWPCookieJar(filename)
    handler = request.HTTPCookieProcessor(cookie)
    opener = request.build_opener(handler)
    response = opener.open("https://www.baidu.com")
    cookie.save(ignore_expires=True, ignore_discard=True)

def read_cookie():
    cookie = cookiejar.LWPCookieJar()
    cookie.load('cookie_LWP.txt', ignore_discard=True, ignore_expires=True)
    handler = request.HTTPCookieProcessor(cookie)
    opener = request.build_opener(handler)
    response = opener.open('https://www.baidu.com')
    print(response.read().decode('utf-8'))

# get_cookie()
# save_cookie_in_Mozilla()
# save_cookie_in_LWP()
read_cookie()