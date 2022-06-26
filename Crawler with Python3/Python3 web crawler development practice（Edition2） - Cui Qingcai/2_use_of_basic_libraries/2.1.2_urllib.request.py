import urllib.request

def request_test():
    request = urllib.request.Request('https://python.org')
    response = urllib.request.urlopen(request)
    print(response.read().decode('utf-8'))

from urllib import request, parse
def multi_parameter_request():
    url = 'https://www.httpbin.org/post'
    headers = {
        'User-Agent': 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)',
        'Host': 'www.httpbin.org'
    }
    dict = { 'name': 'germey' }
    data = bytes(parse.urlencode(dict), encoding = 'utf-8')
    req = request.Request(url = url, data = data, headers = headers, method = 'POST')
    response = request.urlopen(req)
    print(response.read().decode('utf-8'))

# request_test()
multi_parameter_request()