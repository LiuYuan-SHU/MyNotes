from requests import Request, PreparedRequest, Session

url = 'https://www.httpbin.org/post'
data = {'name': 'Germey'}
headers = {
    'User-Agent': 'Mozilla/5.0'
}
s = Session()
req = Request('POST', url, data=data, headers=headers)
prepped = s.prepare_request(req)
r = s.send(prepped)
print(r.text)