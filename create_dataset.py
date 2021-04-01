import random, os, time
import numpy as np
from sys import stdout

def create_file(_max):
    file_name = f'size{_max}.txt'
    with open(file_name, 'w') as file:

        lst = list(np.random.randint(low=10, high=10000, size=_max))
        # print(_max, file=file)
        print(*lst, file=file)
    print('Done', _max)

def create_dir():
    name = 'Datasheet'
    if os.access(name, os.F_OK):
        print(f'{name} folder exist')
    else:
        print(f'{name} folder created')
        os.mkdir(name)
    os.chdir(name)


start = time.time()
data_range = [10**3, 10**4, 10**5, 10**6, 10**7]
create_dir()
for i in data_range:
    create_file(i)
end = time.time()
print(f'Time taken: {end-start} seconds')
