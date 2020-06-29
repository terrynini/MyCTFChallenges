#include <stdio.h>
#include <string.h>

int copy(char *input){

    if(strlen(input) < FLAG_LENGTH)
        return 1;

    COPY_SLOT

    return 0;
}

int main(){
    char input[60];
    scanf("%60s",input);
    if(copy(input))
       puts("Fail");
    else
       puts("Nice"); 
    return 0;
}
