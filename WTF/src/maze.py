# coding: utf-8
import numpy as np
from PIL import Image
import random

size = 1000
def FloodFill(arr, stack):
    d_x = [ 1,0,0,-1]
    d_y = [ 0,1,-1,0]
    while len(stack) != 0:
        x, y = stack.pop()
        road_c = 0
        for d in range(4):
            if arr[x+d_x[d]][y+d_y[d]] == 255:
                road_c += 1
        if road_c < 2:
            arr[x][y] = 255
            adjoin = []
            for d in range(4): 
                if arr[x+d_x[d], y+d_y[d]] == 0:
                    adjoin.append((x+d_x[d], y+d_y[d]))
            random.shuffle(adjoin) 
            stack += adjoin

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

def addBorder(arr,size):
    for i in ([0,size-1]):
        for j in range(size):
            arr[i][j] = 255
            arr[j][i] = 255
def delBorder(arr,size):
    for i in ([0,size-1]):
        for j in range(size):
            arr[i][j] = 0
            arr[j][i] = 0
def putColor(arr):
    pass

import string
flag = input("flag:")

for idx,pic in enumerate(flag):
    arr = np.array([[0]*size]*size)
    arr = np.array(Image.open(f"./{pic}.png").convert("1").convert("L"))
    corner = [(size-3,size-3),(size-3,2),(2,size-3),(2,2)]
    for (x,y) in corner:
        if arr[x][y] == 0:
            start = (x,y) 
    print("Maze generating..")
    addBorder(arr,size)
    s = list()
    s.append(start)
    FloodFill(arr,s)
    s = list()
    s.append(start)
    Fill(arr,s)
    s = list()
    for r in range(len(arr)):
        for c in range(len(arr[0])):
            if arr[r][c] == 255 : 
                arr[r][c] = 0
            if arr[r][c] == 100 or arr[r][c] == 254:
                arr[r][c] = 255
    addBorder(arr,size)
    s.append(corner[(corner.index(start)+1)%len(corner)])
    FloodFill(arr,s)
    print("Complete..")
    img = Image.fromarray(np.uint8(arr),"L")
    img.save(f"challenge_{idx}.png")
