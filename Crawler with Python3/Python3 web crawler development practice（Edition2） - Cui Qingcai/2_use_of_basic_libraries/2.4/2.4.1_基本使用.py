import httpx

def test_get():
    response = httpx.get('https://www.httpbin.org/get')
    print(response.status_code)
    print(response.headers)
    print(response.text)

def test_get_with_headers():
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko)'
                      'Chrome/90.0.4430.93 Safari/537.36'
    }
    response = httpx.get('https://www.httpbin.org/get', headers = headers)
    print(response.text)

def test_httpx_with_http2():
    client = httpx.Client(http2=True)
    response = client.get('https://spa16.scrape.center/')
    print(response.text)

# test_get()
# test_get_with_headers()
test_httpx_with_http2()