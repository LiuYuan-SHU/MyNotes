from pyquery import PyQuery as pq

html = '''
    <div id="container">
        <ul class="list">
            <li class="item-0">first item</li> 
            <li class="item-1"><a href="link2.html">second item</a></li> 
            <li class="item-0 active"><a href="link3.html"><span class="bold">third item</span></a></li> 
            <li class="item-1 active"><a href="link4.html">fourth item</a></li> 
            <li class="item-0"><a href="link5.html">fifth item</a></li> 
        </ul>
    </div>
'''
doc = pq(html)
items = doc(".list")

def search_child_with_find():
    print(type(items))
    print(items)
    lis = items.find('li')
    print(type(lis))
    print(lis)


def search_child_with_children():
    lis = items.children('.active')
    print(lis)


def search_parent_with_parent():
    container = items.parent()
    print(type(container))
    print(container)

def search_parents_with_parents():
    parents = items.parents()
    print(type(parents))
    print(parents)


def search_siblings_with_siblings():
    li = doc('.list .item-0.active')
    print(type(li.siblings()))
    print(li.siblings())

# search_child_with_find()
# search_child_with_children()
# search_parent_with_parent()
# search_parents_with_parents()
search_siblings_with_siblings()