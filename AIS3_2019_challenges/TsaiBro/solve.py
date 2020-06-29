#!/usr/bin/env python3
table = ['a','b','c','d','e','f','g','h',
'i','j','k','l','m','n','o','p',
'q','r','s','t','u','v','w','x',
'y','z','A','B','C','D','E','F',
'G','H','I','J','K','L','M','N',
'O','P','Q','R','S','T','U','V',
'W','X','Y','0','1','2','3','4',
'5','6','7','8','9','{','}','_']

f = open("./flag.txt","r").read().split('\n')[1]
f = f.split("發財")[1:]
for i in range(0,len(f),2):
    print(table[(len(f[i])-1)*8+len(f[i+1])-1],end='')
    
    
