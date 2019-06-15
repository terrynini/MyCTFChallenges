# coding: utf-8
import numpy as np
from PIL import Image
import random

size = 1000

def Fill(arr, stack):
    d_x = [ 1,0,0,-1]
    d_y = [ 0,1,-1,0]
    while len(stack) != 0:
        x, y = stack.pop()
        road_c = 0
        for d in range(4):
            if arr[x+d_x[d]][y+d_y[d]] == 255:
                stack.append((x+d_x[d], y+d_y[d]))
        arr[x][y] = 100

import string

for pic in range(40,51):
    arr = np.array(Image.open(f"./challenge_{pic}.png").convert("1").convert("L"))
    corner = [(size-3,size-3),(size-3,2),(2,size-3),(2,2)]
    for (x,y) in corner:
        if arr[x][y] == 255:
            start = (x,y) 

    s = list()
    s.append(start)
    Fill(arr,s)
    img = Image.fromarray(np.uint8(arr),"L")
    img.save(f"solve_{pic}.png")
    print(f"solve_{pic}.png")
