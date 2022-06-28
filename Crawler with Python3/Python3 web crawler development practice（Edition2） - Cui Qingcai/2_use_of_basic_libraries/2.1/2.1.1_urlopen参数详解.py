import urllib.parse
import urllib.request

"""
def urlopen(url: str | Request,
            data: bytes | None = ...,       # 附加数据
            timeout: float | None = ...,    # 超时限定
            *,
            cafile: str | None = ...,
            capath: str | None = ...,
            cadefault: bool = ...,
            context: SSLContext | None = ...) -> Any
"""

# =============================================
# data参数
# =============================================
# data参数是可选的。在添加该参数时，需要使用 bytes 方法将参数转化为字节流编码格式的内容
# 同时，如果传递了这个参数，那么请求方式就会由 GET 转换为 POST
# 在输出结果中，我们可以看到我们的参数出现在 form 中，这说明是模拟表单提交，用POST方法提交
def data():
    data = bytes(urllib.parse.urlencode({'name': 'germey'}), encoding='utf-8')
    # httpbin 提供HTTP请求测试
    # httpbin/post 用于测试POST请求
    response = urllib.request.urlopen('https://www.httpbin.org/post', data=data)
    print(response.read().decode('utf-8'))

# =============================================
# timeout参数
# =============================================
# 单位：s。如果不指定这个参数，那么会使用全局默认参数
# 运行结果：超时
def timeout():
    response = urllib.request.urlopen('https://www.httpbin.org/get', timeout=0.1)
    print(response.read().decode('utf-8'))

"""
=============================================
其他参数
=============================================
1. context: 指定SSL设置
2. cafile:  CA证书，用于https
3. capath:  CA证书路径
4. cadefault:   已经弃用，默认FALSE
"""

# data()
# timeout()