import re

def greedy():
    content = 'Hello 1234567 World_This is a Regex Demo'
    result = re.match('^He.*(\d+).*Demo$', content)
    print(result)
    print(result.group(1))

def not_greedy():
    content = 'Hello 1234567 World_This is a Regex Demo'
    result = re.match('^He.*?(\d+).*Demo$', content)
    print(result)
    print(result.group(1))

def str_end():
    content = 'http://weibo.com/comment/kEraCN'
    result1 = re.match('http.*?comment/(.*?)', content)
    result2 = re.match('http.*?comment/(.*)', content)
    print('result1: ' + result1.group(1))
    print('result2: ' + result2.group())

greedy()
not_greedy()
str_end()