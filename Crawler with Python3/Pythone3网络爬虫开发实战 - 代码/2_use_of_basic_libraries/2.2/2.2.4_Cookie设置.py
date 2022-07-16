import requests.cookies
from requests import get

def get_cookie():
    r = get('https://www.baidu.com')
    print(r.cookies)
    for key, value in r.cookies.items():
        print(key + ' = ' + value)

def login_with_cookie():
    headers = {
        'Cookie': '_octo=GH1.1.1527798850.1654969812; '
                  '_device_id=4ea8f44437f4811989de234e4e140728; '
                  'user_session=13ry0cfMA6hqgxB6HAmHUQTMNx4jhaLMEYoJ21lCIHCdNTca; '
                  '__Host-user_session_same_site=13ry0cfMA6hqgxB6HAmHUQTMNx4jhaLMEYoJ21lCIHCdNTca; '
                  'logged_in=yes; '
                  'dotcom_user=LiuYuan-SHU; '
                  'has_recent_activity=1; '
                  'color_mode=%7B%22color_mode%22%3A%22auto%22%2C%22light_theme%22%3A%7B%22name%22%3A%22light%22%2C'
                  '%22color_mode%22%3A%22light%22%7D%2C%22dark_theme%22%3A%7B%22name%22%3A%22dark%22%2C%22color_mode'
                  '%22%3A%22dark%22%7D%7D; '
                  'preferred_color_mode=light; '
                  'tz=Asia%2FShanghai; '
                  '_gh_sess=phyqLdlurYAtq4gL6Izou5MY'
                  '%2FNbE7HCTM1CokBv3BoagjCiwzzUFFr9UUb6pxi3432a7krzcfHyHDMrt9o9npGhf7ulfPAWauWrgBTXskQs10oGndtqdrw7fqTBxK9%2FM0%2B6NEGMAMwT4fRxKb3MoARP%2F6ZIXlihuQBt3oDSu5OujjD4v8XNCDeI54wxCwy1e--dBn8lVA1eN%2Bjwnn7--LafwTv6XUdCxVw1d9mFgfA%3D%3D '
    }
    r = get('https://www.github.com', headers=headers)
    print(r.text)

def request_cookie_jar():
    cookies = '_octo=GH1.1.1527798850.1654969812; ' \
              '_device_id=4ea8f44437f4811989de234e4e140728; ' \
              'user_session=13ry0cfMA6hqgxB6HAmHUQTMNx4jhaLMEYoJ21lCIHCdNTca; ' \
              '__Host-user_session_same_site=13ry0cfMA6hqgxB6HAmHUQTMNx4jhaLMEYoJ21lCIHCdNTca; ' \
              'logged_in=yes; ' \
              'dotcom_user=LiuYuan-SHU; ' \
              'has_recent_activity=1; ' \
              'color_mode=%7B%22color_mode%22%3A%22auto%22%2C%22light_theme%22%3A%7B%22name%22%3A%22light%22%2C%22color_mode%22%3A%22light%22%7D%2C%22dark_theme%22%3A%7B%22name%22%3A%22dark%22%2C%22color_mode%22%3A%22dark%22%7D%7D; preferred_color_mode=light; tz=Asia%2FShanghai; ' \
              '_gh_sess=phyqLdlurYAtq4gL6Izou5MY%2FNbE7HCTM1CokBv3BoagjCiwzzUFFr9UUb6pxi3432a7krzcfHyHDMrt9o9npGhf7ulfPAWauWrgBTXskQs10oGndtqdrw7fqTBxK9%2FM0%2B6NEGMAMwT4fRxKb3MoARP%2F6ZIXlihuQBt3oDSu5OujjD4v8XNCDeI54wxCwy1e--dBn8lVA1eN%2Bjwnn7--LafwTv6XUdCxVw1d9mFgfA%3D%3D'
    jar = requests.cookies.RequestsCookieJar()
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.116 Safari/537/36'
    }
    for cookie in cookies.split(';'):
        key, value = cookie.split('=')
        jar.set(key, value)
    r = requests.get('https://www.github.com', cookies=jar, headers=headers)
    print(r.text)

# get_cookie()
# login_with_cookie()
request_cookie_jar()