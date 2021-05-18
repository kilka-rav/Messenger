import os

name = []
name1 = []

for i in os.walk('data/user/friends'):
    name.append(i[1])
def my_write(name):
    f = open('data/user/list_friend.txt', 'w')
    for i in name[0]:
        f.write(i)
        f.write("\n")
    f.close()

my_write(name)

