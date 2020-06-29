#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//XTEA wiki
void encipher(uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], sum=0, delta=0x9E3779B9;
    for (i=0; i < 64; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
    }
    v[0]=v0; v[1]=v1;
}
/*
void decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], delta=0x9E3779B9, sum=delta*num_rounds;
    for (i=0; i < num_rounds; i++) {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    }
    v[0]=v0; v[1]=v1;
}
*/
int main(){
    char* input;
    puts("My encryptor 0.1");
    puts("I didn't implement the decryptor");
    puts("So,you'll never find out my secret unless I am drunk");
    scanf("%ms", &input);
    int input_l = strlen(input);
    int expand = ((input_l/8)+1)*8;
    input = realloc(input, sizeof(char)*(expand+1));
    for(int i = expand; i >= input_l ; i--){
        input[i] = 0;
    }    
    uint32_t const key[4] = {1198484580,1114600052,1247896677,1383424633}; 

    for(int r = 0; r < (expand/8)+1 ; r++){
        encipher(input,key); //encipher(input+r*8,key);
    }

    for(int i = 0; i < expand ; i++)
        printf("%02hhx",input[i]);
    /*
    for(int r = 0; r<9  ; r++){
        decipher(64,input,key);
    }
    puts("");
    
    for(int i = 0; i < expand ; i++)
        printf("%c",input[i]);
    */
    free(input);
    input = 0;
}
