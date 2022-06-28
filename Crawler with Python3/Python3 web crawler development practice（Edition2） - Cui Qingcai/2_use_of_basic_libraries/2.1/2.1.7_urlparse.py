from urllib.parse import urlparse

def urlparse_test():
    result = urlparse('https://www.baidu.com/index.html;user?id=5#commit')
    print(type(result))
    print(result)

def scheme_test():
    result = urlparse('www.baidu.com/index.html;user?id=5#commit', scheme='https')
    print(type(result))
    print(result)

# urlparse_test()
scheme_test()