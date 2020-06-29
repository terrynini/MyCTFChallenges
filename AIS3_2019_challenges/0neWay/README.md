# insert the jpg into c

```sh
objcopy -I binary -O elf64-x86-64 -B i386:x86-64 flag.jpg data.o
gcc 0neWay.c data.o -o 0neWay
```
