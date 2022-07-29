import requests     # HTML请求
import json         # json文件分析
import pymongo      # MongoDB连接
import logging      # 日志打印

# 日志初始化
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s - %(levelname)s: %(message)s')

# 数据库设置
MONGO_CONNECTION_STRING = 'mongodb://localhost:27017'
MONGO_DB_NAME = 'movies'
MONGO_COLLECTION_NAME = 'movies'
client = pymongo.MongoClient(MONGO_CONNECTION_STRING)
db = client[MONGO_DB_NAME]
collection = db[MONGO_COLLECTION_NAME]

# 全局变量
# 列表页Ajax请求URL，需要补齐offset，每次从0开始，每次递增10，直到=MAX_LIST_PAGE * 10
AJAX_LIST_without_offset = 'https://spa1.scrape.center/api/movie?limit=10&offset='
# 电影详情页AJax请求URL，需要补齐id，从1开始，每次递增1，直到=MAX_ID
AJAX_DETAIL_without_id = 'https://spa1.scrape.center/api/movie/'
MAX_LIST_PAGE = 9
MAX_ID = 100


# 根据提供的url来调用requests.get，返回response的json数据
# 并不检查url的正确性
def get_json(url):
    logging.info('scraping %s ...\n', url)
    try:
        response = requests.get(url=url)
        if response.status_code == 200:
            json_data = response.json()
            return json_data
        logging.error('got invalid response state code %d when scraping %s', response.status_code, url)
    except requests.RequestException:
        logging.error('error occurred while scraping %s\n', url)


# 爬取电影列表信息
def scrape_list():
    for offset in range(0, MAX_LIST_PAGE + 1):
        ajax_list_url = AJAX_LIST_without_offset + str(offset * 10)
        json_data = get_json(ajax_list_url)
        yield json_data


# 爬取电影详细信息
def scrape_detail(detail_id):
    ajax_detail_url = AJAX_DETAIL_without_id + str(detail_id)
    json_data = get_json(ajax_detail_url)
    yield json_data


# 保存数据到MongoDB
def save_data(json_data):
    logging.info('saving data for id equals %d\n', json_data.get('id'))
    data = {
        'name': json_data.get('name'),
        'alias': json_data.get('alias'),
        'cover': json_data.get('cover'),
        'categories': json_data.get('categories'),
        'regions': json_data.get('regions'),
        'drama': json_data.get('drama')
    }
    update = collection.update_one(
        {
            'name': data.get('name')
        },
        {'$set': data},
        upsert=True
    )
    if update.upserted_id != None:
        logging.info('data insert/update successfully')
    else:
        logging.info('data update failed')


def main():
    # 获得列表页数据
    for data in scrape_list():
        # 遍历列表页数据ID，生成详情页Ajax请求URL
        for item in data.get('results'):
            detail_id = item.get('id')
            detail_datas = scrape_detail(detail_id=detail_id)
            for detail_data in detail_datas:
                save_data(json_data=detail_data)


if __name__ == '__main__':
    main()
