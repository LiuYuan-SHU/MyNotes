import requests                     # HTML获取
from pyquery import PyQuery as pq   # HTML解析：CSS选择器
import re                           # 正则表达式匹配
import logging                      # 日志打印

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s - %(levelname)s : %(message)s')
URL = 'https://ssr1.scrape.center/'
# 获取HTML文本
html = requests.get(url=URL).text
# 将HTML文本转换为PyQuery对象
doc = pq(html)
# 获取电影列表
items = doc('.el-card').items()

# 生成保存文件
file = open('movies.txt', 'w', encoding='utf-8')
# 遍历列表中的每一部电影
for item in items:
    # 电影名称
    name = item('.name').text()
    file.write(f'名称：{name}\n')
    # 类别
    # 此处用到了python的列表表达式
    categories = [item.text() for item in item.find('.categories button span').items()]
    file.write(f'类别：{categories}\n')
    # 上映时间
    publish_time_pattern = re.compile('(\d{4}-\d{2}-\d{2})')
    publish_time = re.search(publish_time_pattern, item.text()).group(1) \
        if re.search(publish_time_pattern, item.text()) else None
    file.write(f'上映时间：{publish_time}\n')
    # 评分
    score = item('.score').text()
    file.write(f'评分：{score}\n')
    # 分割线
    file.write(f'{"=" * 50}\n')
    logging.info(f'完成条目：{name}')

file.close()
