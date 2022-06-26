import urllib.request as request

# 抓取Python官网
def getResponse():
    response = request.urlopen('https://www.python.org')
    # 打印整个网页
    # print(response.read().decode('utf-8'))
    # 打印相应类型
    print(type(response))

# 获取响应状态码：200：成功
def getResponse_StatusCode():
    response = request.urlopen('https://www.python.org')
    print(response.status)

# 提取响应头信息
def getResponse_headInfo():
    response = request.urlopen('https://www.python.org')
    # 获取响应头信息
    print(response.getheaders())
    # 获取响应头中的Server值，得知网页是使用nginx搭建的
    print(response.getheader('Server'))

# getResponse()
# getResponse_StatusCode()
# getResponse_headInfo()