#!/usr/bin/env python3
import numpy as np
from PIL import Image
import random
import string

f = open("./flag.dump","r").read().split(',')
w = 650
h = 410
arr = np.zeros([h,w])
for i in range(h):
    for j in range(w):
        arr[i][j] = 255 if f[i*w+j] == '1' else 0
img = Image.fromarray(np.uint8(arr),"L")
img.save("flag.png")
