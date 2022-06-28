from requests import get

def get_test():
    data = {
        'name': 'germey',
        'age': 25
    }
    r = get('https://www.httpbin.org/get', params=data)
    print(r.text)

def get_json():
    r = get('https://www.httpbin.org/get')
    print(r.json())

# get_test()
get_json()