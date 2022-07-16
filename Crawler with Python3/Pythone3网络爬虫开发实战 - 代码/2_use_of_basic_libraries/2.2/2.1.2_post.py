from requests import post

data = {
    'name': 'germey',
    'age': 25
}
response = post('https://www.httpbin.org/post', data=data)
print(response.text)