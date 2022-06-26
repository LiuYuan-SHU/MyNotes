import urllib.request

# 如果需要往请求中加入Headers等信息，就需要Request类来构建请求

# 1. 通过独立构造Request对象，我们可以：
#   1.1 将请求独立生成成一个对象
#   1.2 更加丰富和灵活地配置参数
request = urllib.request.Request('https://python.org')

response = urllib.request.urlopen(request)
print(response.read().decode('utf-8'))