import httpx

def test_get():
    response = httpx.get('https://www.httpbin.org/get')
    print(response.status_code)
    print(response.headers)
    print(response.text)

def test_get_with_headers():


test_get()