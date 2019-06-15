#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char _binary_flag_jpg_start;
extern char _binary_flag_jpg_end;

unsigned long hash(unsigned char *str)
{ 
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main(){
    char data[30] = {0};
    int idx = 0;
    puts("-----");
    puts("I encrypted a image in this binary,");
    puts("you have to answer my questions to decrypt it,");
    puts("cuz only my friends can view this secret image");
    puts("-----");
    puts("Who am I? (lowercase)");
    scanf("%4s",&data[idx]);
    idx = strlen(data);
    puts("How old am I?");
    scanf("%2s", &data[idx]);
    idx = strlen(data);
    puts("What the name of my first pet? (lowercase)");
    scanf("%20s",&data[idx]);
    idx = strlen(data);
    printf("%s, %lu, %d, %lu\n",data, hash(data), idx, hash((char*)&idx));
    if( hash((char*)&idx) != 177593 || hash(data) != 8932587927620123215){
        puts("haker haker go away");
        return -1;
    }
    else{
        char* ptr =  &_binary_flag_jpg_start;
        int iter = 0;
        FILE* flag = fopen("./flaggggg.jpg","w");
        if ( flag == NULL){
            puts("write file error !");
            return -2;
        }
        while( ptr != &_binary_flag_jpg_end){
            *ptr ^= data[ iter++%idx ];
            fwrite(ptr++, 1, 1,flag);
        }
        puts("you got my secret photo");
        fclose(flag);
    }
    return 0;
}
