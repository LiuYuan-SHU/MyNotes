import asyncio
import json
import aiohttp
import logging
from motor.motor_asyncio import AsyncIOMotorClient

# 日志信息配置
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s: %(message)s')

# MongoDB连接配置
MONGO_CONNECTION_STRING = 'mongodb://localhost:27017'
MONGO_DB_NAME = 'books'
MONGO_COLLECTION_NAME = 'books'

client = AsyncIOMotorClient(MONGO_CONNECTION_STRING)    # 获取连接
db = client[MONGO_DB_NAME]                              # 选择数据库
collection = db[MONGO_COLLECTION_NAME]                  # 选择数据表

# 定义URL
INDEX_URL = 'https://spa5.scrape.center/api/book/?limit=18&offset={offset}'
DETAIL_URL = 'https://spa5.scrape.center/api/book/{id}'

PAGE_SIZE = 18          # 列表加载偏移量
PAGE_NUMBER = 503       # 列表页数
TEST_PAGE_NUMBER = 10   # 测试用列表页数
CONCURRENCY = 10        # 最大并发量

semaphore = asyncio.Semaphore(CONCURRENCY)  # 信号量对象
session = None


# 根据提供的URL，返回JSON数据，不检查URL的正确性
async def get_json_data(url):
    logging.info('getting json of %s', url)
    async with semaphore:
        try:
            async with session.get(url) as response:
                return await response.json()
        except aiohttp.ClientError:
            logging.error('error occurred while scraping %s', url, exc_info=True)


# 测试 get_json_data 函数
# 测试通过
async def test_get_json_data():
    global session
    session = aiohttp.ClientSession()
    json_data = await get_json_data('https://spa5.scrape.center/api/book/?limit=18&offset=0')
    print(json.dumps(json_data['results'][0], indent=2, ensure_ascii=False))
    await session.close()

# 将数据异步存储到MongoDB中
async def save_data(data):
    logging.info('saving data %s', data)
    if data:
        return await collection.update_one({
                'id': data.get('id')
            },
            {
                '$set': data
            }, upsert=True)


# 爬取列表页JSON数据
async def scrape_index(page_number):
    index_url = INDEX_URL.format(offset = PAGE_SIZE * (page_number - 1))
    return await get_json_data(index_url)


# 爬取详情页JSON数据
async def scrape_detail(item_id):
    detail_url = DETAIL_URL.format(id = item_id)
    data = await get_json_data(detail_url)
    await save_data(data)


async def main():
    # 定义全局变量session
    global session
    session = aiohttp.ClientSession()

    # 生成列表页URL并异步爬取
    scrape_index_tasks = [asyncio.ensure_future(scrape_index(page)) for page in range(1, PAGE_NUMBER + 1)]
    results = await asyncio.gather(*scrape_index_tasks)

    # 将爬取到的结果中的id提取出来，然后爬取详情页
    ids = []
    # 遍历请求到的Ajax数据
    for index_data in results:
        # 如果Ajax为空，跳过
        if not index_data: continue
        # 遍历其中的results字段，再遍历其中的id字段
        for item in index_data.get('results'):
            ids.append(item.get('id'))

    scrape_detail_tasks = [asyncio.ensure_future(scrape_detail(item_id)) for item_id in ids]
    await asyncio.wait(scrape_detail_tasks)

    await session.close()


if __name__ == '__main__':
    # 调用 get_json_data 函数的测试函数
    # asyncio.get_event_loop().run_until_complete(test_get_json_data())

    asyncio.get_event_loop().run_until_complete(main())

