#!/usr/bin/env python3
f = open("output.txt",'r').read().split('\n')[:-1]
def rearrange( arg ):
    arg = bytearray(arg,'ascii')
    for i in range(0,len(arg),4):
        a = arg[i]
        b = arg[i+1]
        c = arg[i+2]
        d = arg[i+3]
        arg[i+1] = d
        arg[i+2] = a
        arg[i] = b
        arg[i+3] = c
    return arg.decode('ascii')
    
for i in f:
    print(rearrange(i))
    
