from secret import flag
from hashlib import md5

def rearrange( arg ):
    arg = bytearray(arg,'ascii')
    for i in range(0,len(arg),4):
        a = arg[i]
        b = arg[i+1]
        c = arg[i+2]
        d = arg[i+3]
        arg[i+2] = d
        arg[i+1] = a
        arg[i+3] = b
        arg[i] = c
    return arg.decode('ascii')

flag += b"0"*(len(flag)%4)

for i in range(0,len(flag),4):
    print(rearrange(md5(bytes(flag[i:i+4])).hexdigest()))
