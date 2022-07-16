import httpx

# 方法一
with httpx.Client() as client:
    response = client.get('https://www.httpbin.org/get')
    print(response)

# 方法二
client = httpx.Client()
try:
    response = client.get('https://www.httpbin.org/get')
    print(response)
finally:
    response.close()