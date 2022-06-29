import requests

files = {'files': open('favicon.ico', 'rb')}
r = requests.post('https://www.httpbin.org/post', files=files)
print(r.text)