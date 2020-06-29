#include <stdio.h>
#include <string.h>
#ifdef DEBUG
#define debug() {for(int i = 0;i<400;i++)printf("%hhu,",memory[i]);for(int i = 0;i<400;i++)printf("%c,",memory[i]);}
#else
#define debug()
#endif

char memory[400];
char code[] = "-------------------------------------------------------------------[>[-]<[-]]>[>--------------------------------------------------------[>[-]<[-]]>[>-------------------------------------------------------[>[-]<[-]]>[>------------------------------------------------------[>[-]<[-]]>[>---------------------------------------------------[>[-]<[-]]>[>---------------------------------[>[-]<[-]]>[>>----[---->+<]>++.++++++++.++++++++++.>-[----->+<]>.+[--->++<]>+++.>-[--->+<]>-.[---->+++++<]>-.[-->+<]>---.[--->++<]>---.++[->+++<]>.+[-->+<]>+.[--->++<]>---.++[->+++<]>.+++.[--->+<]>----.[-->+<]>-----.[->++<]>+.-[---->+++<]>.--------.>-[--->+<]>.-[----->+<]>-.++++++++.--[----->+++<]>.+++.[--->+<]>-.-[-->+<]>---.++[--->+++++<]>.++++++++++++++.+++[->+++++<]>.[----->+<]>++.>-[----->+<]>.---[->++<]>-.++++++.[--->+<]>+++.+++.[-]]]]]]]";
int main(){
    memset(memory,0,sizeof(memory));
    char* ptr = memory;
    char input[6] = {0};
    int loop;
    puts("Tell me a joke, if it's good enough, I'll show you the flag");
    scanf("%6s", input);
    for(int i = 0 ; i < 6 ; i++){
        memory[2*i] = input[i];
        memory[2*i+1] = 1;
    }
    for(char* pc = code;*pc;pc++){
        switch(*pc){
            case '+':
                ++*ptr;
                break;
            case '-':
                --*ptr;
                break;
            case '>':
                ++ptr;
                break;
            case '<':
                --ptr;
                break;
            case '[':
                if(!(*ptr)){
                    loop = 1;
                    while (loop > 0) {
                        pc++;
                        if (*pc == '[') 
                            loop++;
                        else if ( *pc == ']')
                            loop--;
                    }
                }
                break;
            case ']':
                if(*ptr){
                    loop = 1;
                    while (loop > 0) {
                        pc--;
                        if (*pc == '[') 
                            loop--;
                        else if ( *pc == ']')
                            loop++;
                    }
                }
                break;
            case '.':
                printf("%c",*ptr);
                break;
        }
    }
    puts("\nNuh, idk, probably");
    debug();
}
