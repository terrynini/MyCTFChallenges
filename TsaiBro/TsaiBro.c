#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char table[64] = {'a','b','c','d','e','f','g','h',
'i','j','k','l','m','n','o','p',
'q','r','s','t','u','v','w','x',
'y','z','A','B','C','D','E','F',
'G','H','I','J','K','L','M','N',
'O','P','Q','R','S','T','U','V',
'W','X','Y','0','1','2','3','4',
'5','6','7','8','9','{','}','_'};

int main(int argc, char** argv){
    char temp[9];
    if(argc == 1){
        printf("./TsaiBro string");
        return 0;
    }
    puts("Terry...逆逆...沒有...學問...單純...分享...個人...生活...感觸...");

    for( int i = 0 ; i < strlen(argv[1]) ; i++){
        for(int j = 0 ; j < 64; j ++)
            if(table[j] == argv[1][i]){
                printf("發財%.*s發財%.*s",j/8+1,"..........",(j%8)+1,"...........");
                break;
            }
    }
    return 0;
}
