import logging

from requests import get
from requests.packages import urllib3

def get_without_verify():
    response = get('https://ssr2.scrape.center')
    print(response.status_code)

def get_with_verify():
    response = get('https://ssr2.scrape.center', verify=False)
    print(response.status_code)

def get_with_verify_disable_warning_method1():
    urllib3.disable_warnings()
    response = get('https://ssr2.scrape.center', verify=False)
    print(response.status_code)

def get_with_verify_disable_warning_method2():
    logging.captureWarnings(True)
    response = get('https://ssr2.scrape.center', verify=False)
    print(response.status_code)


# get_without_verify()
# get_with_verify()
# get_with_verify_disable_warning_method1()
get_with_verify_disable_warning_method2()