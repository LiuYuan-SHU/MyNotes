import pymysql

db = pymysql.connect(host='localhost', user='root', password='lhr20011228', port=3306)
cursor = db.cursor()

data = {
    'id': '20120001',
    'name': 'Bob',
    'age': 22
}

table = 'test.students'
keys = ', '.join(data.keys())
values = ', '.join(['%s'] * len(data))

sql = 'INSERT INTO {table}({keys}) VALUES({values}) ON DUPLICATE KEY UPDATE '.format(table=table, keys=keys,
                                                                                     values=values)
update = ', '.join(["{key} = %s".format(key=key) for key in data])
sql += update
print(sql)

try:
    print(tuple(data.values()) * 2)
    if cursor.execute(sql, tuple(data.values()) * 2):
        print('Successful')
        db.commit()
    else:
        print('SQL executed successfully but no rows were effected')
except:
    print('Failed')
db.close()
