'''
项目分析：
    1. 目标网站： https://ssr1.scrape.center
    2. 需求：
        1. 利用requests爬取这个沾点的每一页的电影列表，顺着列表再爬取每个电影的详情页
        2，用正则表达式提取每部电影的名称、封面、类别、上映时间、评分、剧情简介等内容
        3. 把以上爬取的内容保存为JSON文件
        4. 使用多进程实现爬取的加速
    3. 分析：
        1. 定性分析：
            1. 电影列表URL：https://ssr1.scrape.center/page/1 ~ 11
            2. 电影详情页：当前url/detail/{id} 1 ~ 100
        2. 动态分析：
            1. 每一步电影在列表中都是一个div节点，这些节点的class属性中都有一个el-card属性值，我们可以用这个进行提取
        3. 详情页爬取分析：
            封面：img节点，class属性为cover
            名称：h2节点，
            类别：span节点，外层是button节点，再外层是一个class为categories的div节点
            上映时间：span节点，外层是class为m-v-sm info的div
            评分：p节点，class属性为score
            剧情简介：p节点，外侧class为drama的div节点
        4. 结果保存
            首先定义一个保存数据的文件夹RESULTS_DIR，然后判断这个文件夹是否存在，如果不存在的话就创建一个
            然后将电影的名称作为文件名称，然后用json.dump方法将字典转换为json文件

'''

import logging  # 输出信息
import requests  # 基础请求库
import re  # 正则表达式
from urllib.parse import urljoin  # url拼接
import json  # 将字典转换为JSON文件
from os import makedirs  # 创建文件夹指令
from os.path import exists  # 判断是否存在一个文件节点
import multiprocessing  # 多进程

# 定义日志的输出级别和输出格式
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s - %(levelname)s: %(message)s')
# 储存站点基础URL
BASE_URL = 'https://ssr1.scrape.center'
# 记录列表的页数
TOTAL_PAGE = 10
# 保存结果的文件夹名称
RESULTS_DIR = 'results'


# 考虑到要爬取的网页既有列表也有详情，所以定义一个较为通用的爬取函数
# 返回页面的HTML代码
def scrape_page(url):
    # 打印日志
    logging.info('scraping %s...', url)
    try:
        # 获取网页
        response = requests.get(url)

        # 如果正常响应
        if response.status_code == 200:
            return response.text
        # 如果错误响应
        logging.error('get invalid status code %s while scraping %s', response.status_code, url)
    except requests.RequestException:
        logging.error('error occured while scraping %s', url, exc_info=True)


# 定义列表爬取方法：生成URL，并且调用scrape_page函数，返回网页HTML
def scrape_index(page):
    # f开头的字符串表示，将大括号及大括号中的内容更替为内容对应的变量
    index_url = f'{BASE_URL}/page/{page}'
    return scrape_page(index_url)


# 解析列表页，并得到每部电影的详情页URL，将这些URL逐一返回
def parse_index(html):
    # 定义正则表达式匹配模式，获得详情页的URL
    pattern = re.compile('<a.*?href="(.*?)".*?class="name">')
    # 记录返回的列表
    items = re.findall(pattern, html)
    # 如果返回的列表是空
    if not items:
        return []
    # 遍历列表，生成详情页URL并返回
    for item in items:
        detail_url = urljoin(BASE_URL, item)
        logging.info('get detail url %s', detail_url)
        # yield相当于return，具体区别看：https://blog.csdn.net/mieleizhi0522/article/details/82142856/
        yield detail_url


# 获取详情页的HTML
# 之所以这里直接调用之前的通用方法，好处有两个：
#   1. 有利于理顺代码逻辑
#   2. 有利于在之后的有需求的时候做出改动，灵活性更好
def scrape_detail(url):
    return scrape_page(url)


# 对详情页URL进行正则表达式分割，获取其中的目标内容
def parse_detail(html):
    # 封面正则表达式
    cover_pattern = re.compile('class="item.*?<img.*?src="(.*?)@.*?".*?class="cover">', re.S)
    # 名称正则表达式
    title_pattern = re.compile('<h2.*?class="m-b-sm">(.*?)</h2>')
    # 标签正则表达式
    tab_pattern = re.compile('<button.*?category.*?<span>(.*?)</span>.*?</button>', re.S)
    # 发行时间正则表达式
    publish_pattern = re.compile('(\d{4}-\d{2}-\d{2})\s?上映')
    # 评分正则表达式
    score_pattern = re.compile('score.*?>(.*?)<', re.S)
    # 剧情简介正则表达式
    drama_pattern = re.compile('<div.*?drama.*?>.*?<p.*?>(.*?)</p', re.S)

    # 获取封面URL
    cover_html = re.search(cover_pattern, html).group(1).strip() if re.search(cover_pattern, html) else None
    # 获取名称
    title = re.search(title_pattern, html).group(1).strip() if re.search(title_pattern, html) else None
    # 获取标签
    categories = re.findall(tab_pattern, html) if re.findall(tab_pattern, html) else []
    # 获取发行时间
    publish_time = re.search(publish_pattern, html).group(1).strip() if re.search(publish_pattern, html) else None
    # 获取评分
    score = re.search(score_pattern, html).group(1).strip() if re.search(score_pattern, html) else None
    # 获取简介
    drama = re.search(drama_pattern, html).group(1).strip() if re.search(drama_pattern, html) else None

    return {
        'cover': cover_html,
        'title': title,
        'categories': categories,
        'publish_time': publish_time,
        'score': score,
        'drama': drama
    }


# 保存文件
def save_data(data):
    name = data.get('title')
    data_path = f'{RESULTS_DIR}/{name}.json'
    json.dump(data, open(data_path, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)


# 定义main函数
# 由于main函数是多进程调用的，因此只负责一页列表页上的信息，因此传入一个page作为目标页即可
def main(page):
    # 获得列表页的HTML
    index_html = scrape_index(page)
    # 对列表页HTML进行解析，获得详细页URL
    detail_urls = parse_index(index_html)
    # 遍历获得的URL
    for detail_url in detail_urls:
        # 获得详细页HTML
        detail_html = scrape_detail(detail_url)
        # 获得电影data
        data = parse_detail(detail_html)
        # 保存到JSON文件中
        save_data(data)
        logging.info('data saved successfully')


if __name__ == '__main__':
    # 判断存放结果的文件夹是否存在，如果不存在就创建一个
    exists(RESULTS_DIR) or makedirs(RESULTS_DIR)

    # 生成进程池
    pool = multiprocessing.Pool()
    # 确定page的范围
    pages = range(1, TOTAL_PAGE + 1)
    # 遍历pages中的内容，分别传递给main
    # 每次调用main就会生成一个进程，加入到进程池中
    # 根据机器的CPU有多少个核，进程池的大小就会默认设置为几
    pool.map(main, pages)
    pool.close()
    pool.join()
