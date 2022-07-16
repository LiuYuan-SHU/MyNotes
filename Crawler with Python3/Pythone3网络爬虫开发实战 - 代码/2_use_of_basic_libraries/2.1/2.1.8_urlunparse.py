from urllib.parse import urlparse, urlunparse

def urlunparse_test():
    data = ['https', 'www.baidu.com', 'index.html', 'user', 'a=6', 'comment']
    print(urlunparse(data))

urlunparse_test()