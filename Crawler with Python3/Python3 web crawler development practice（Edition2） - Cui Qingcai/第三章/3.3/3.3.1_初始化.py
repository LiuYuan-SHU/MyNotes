from pyquery import PyQuery as pq


def init_string():
    html = '''
    <div>
        <ul>
            <li class="item-0">first item</li> 
            <li class="item-1"><a href="link2.html">first item</a></li> 
            <li class="item-0 active"><a href="link3.html"><span class="bold">first item</span></a></li> 
            <li class="item-1 active"><a href="link4.html">first item</a></li> 
            <li class="item-0"><a href="link5.html">first item</a></li> 
        </ul>
    </div>
    '''
    doc = pq(html)
    print(doc('li'))


def init_ULR():
    doc = pq(url='https://cuiqingcai.com')
    print(doc('title'))

def init_file():
    doc = pq(filename='../3.1/test.html')
    print(doc('title'))

# init_string()
# init_ULR()
init_file()