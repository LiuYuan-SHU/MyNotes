import aiohttp
import asyncio


async def main(json = False):
    data = {'name': 'Liuyuan', 'age': 21}
    async with aiohttp.ClientSession() as session:
        if json:
            async with session.post('https://www.httpbin.org/post', data=data) as response:
                print(await response.text())
        else:
            async with session.post('https://www.httpbin.org/post', json=data) as response:
                print(await response.text())


if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(main())