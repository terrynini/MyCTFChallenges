# coding: utf-8
import random
import string
import ctypes

dl = 70    
total = 1000

def v1(data, l):
    temp = []
    for i in range(l):
        temp.append(ord(data[i])*5566)
    return temp
def v2(data, l):
    temp = []
    for i in range(l):
        v5 = 0
        for j in range(ord(data[i])):
            if j & 1 == 1:
                v5 += 1
            else:
                v5 += 3
        temp.append(v5)
    return temp
def v3(data, l):
    temp = []
    for i in range(l):
        temp.append((ord(data[i])^5566)&0xffffffff)
    return temp
def v4(data, l):
    temp = []
    for i in range(l):
        v5 = 0xdeadbeef
        for j in range(ord(data[i])):
            if j & 1 == 1:
                v5 = ctypes.c_uint32(v5-0x5566).value
        temp.append(v5)
    return temp
def v5(data, l):
    temp = []
    for i in range(l):
        pp = 0
        p = 1
        v5 = 0
        for j in range(ord(data[i])):
            v5 = pp+p
            pp = p
            p = v5
        temp.append(ctypes.c_uint32(v5).value)
    return temp
gen = {}
gen['verify_1'] = v1
gen['verify_2'] = v2
gen['verify_3'] = v3
gen['verify_4'] = v4
gen['verify_5'] = v5
flag = []
keys = ''
for r in range(total):
    l = 0
    lis = []
    key = random.sample((string.digits+string.ascii_uppercase)*3,70)
    while l < dl:
        temp = {}
        temp['func'] = f"verify_{random.randint(1,5)}"
        temp['offset'] = random.randint(0x1831,0x9876)
        temp['chr_idx'] = l

        _len = random.randint(1,2)
        while l + _len > dl and _len > 0 :
            _len -= 1
        temp['check_len'] = _len
        temp['verify'] = gen[temp['func']]( key[l:l+_len] ,_len)
        if len(temp['verify']) == 1:
            temp['verify'].append(0)
        l += _len
        lis.append(temp)
    random.shuffle(lis)
    flag.append(lis)
    keys += ''.join(key) +'\n'

flag = [x for i in flag for x in i]
f = open("./flag.h","w")
line = f"struct Check data[{len(flag)}] = {{"
for it in flag:
        line += f"{{&{it['func']}-{it['offset']},0,{it['offset']},{it['chr_idx']},{it['check_len']},{repr(it['verify']).replace(']','}').replace('[','{')}}},"
line = line[:-1] + "};"
f.write(line)
f.close()
f = open("./key.txt","w")
f.write(keys)
f.close()
