from requests import get, post, Session

def cookie_without_session():
    get('https://www.httpbin.org/cookies/set/number/123456789')
    r = get('https://www.httpbin.org/cookies')
    print(r.text)

def cookie_with_session():
    s = Session()
    s.get('https://www.httpbin.org/cookies/set/number/123456789')
    r = s.get('https://www.httpbin.org/cookies')
    print(r.text)

cookie_without_session()
cookie_with_session()
