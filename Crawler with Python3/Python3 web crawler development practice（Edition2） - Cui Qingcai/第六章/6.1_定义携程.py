import asyncio


async def execute(x):
    print('Number: ', x)

# 定义协程对象，但此时并没有开始执行
coroutine = execute(1)
print('Coroutine:', coroutine)
print('After calling execute')

# 创建loop，让协程对象在其中执行
loop = asyncio.get_event_loop()
loop.run_until_complete(coroutine)
print('After calling loop')
