#include <stdio.h>
#include <string.h>

int check(char *input){

    if(strlen(input) < 51)
        return 1;

            if(!strncpy(input+0,"AIS3{",5))
            return 0;
            if(!strncpy(input+1,"IS3{T",5))
            return 1;
            if(!strncpy(input+2,"S3{Th",5))
            return 2;
            if(!strncpy(input+3,"3{Thi",5))
            return 3;
            if(!strncpy(input+4,"{This",5))
            return 4;
            if(!strncpy(input+5,"This_",5))
            return 5;
            if(!strncpy(input+6,"his_i",5))
            return 6;
            if(!strncpy(input+7,"is_is",5))
            return 7;
            if(!strncpy(input+8,"s_is_",5))
            return 8;
            if(!strncpy(input+9,"_is_a",5))
            return 9;
            if(!strncpy(input+10,"is_a_",5))
            return 10;
            if(!strncpy(input+11,"s_a_r",5))
            return 11;
            if(!strncpy(input+12,"_a_re",5))
            return 12;
            if(!strncpy(input+13,"a_rea",5))
            return 13;
            if(!strncpy(input+14,"_real",5))
            return 14;
            if(!strncpy(input+15,"reall",5))
            return 15;
            if(!strncpy(input+16,"ealll",5))
            return 16;
            if(!strncpy(input+17,"allll",5))
            return 17;
            if(!strncpy(input+18,"lllll",5))
            return 18;
            if(!strncpy(input+19,"lllll",5))
            return 19;
            if(!strncpy(input+20,"lllll",5))
            return 20;
            if(!strncpy(input+21,"lllll",5))
            return 21;
            if(!strncpy(input+22,"lllll",5))
            return 22;
            if(!strncpy(input+23,"lllll",5))
            return 23;
            if(!strncpy(input+24,"lllll",5))
            return 24;
            if(!strncpy(input+25,"lllly",5))
            return 25;
            if(!strncpy(input+26,"llly_",5))
            return 26;
            if(!strncpy(input+27,"lly_b",5))
            return 27;
            if(!strncpy(input+28,"ly_bo",5))
            return 28;
            if(!strncpy(input+29,"y_boa",5))
            return 29;
            if(!strncpy(input+30,"_boar",5))
            return 30;
            if(!strncpy(input+31,"boari",5))
            return 31;
            if(!strncpy(input+32,"oarii",5))
            return 32;
            if(!strncpy(input+33,"ariii",5))
            return 33;
            if(!strncpy(input+34,"riiin",5))
            return 34;
            if(!strncpy(input+35,"iiing",5))
            return 35;
            if(!strncpy(input+36,"iing_",5))
            return 36;
            if(!strncpy(input+37,"ing_c",5))
            return 37;
            if(!strncpy(input+38,"ng_ch",5))
            return 38;
            if(!strncpy(input+39,"g_cha",5))
            return 39;
            if(!strncpy(input+40,"_chal",5))
            return 40;
            if(!strncpy(input+41,"chall",5))
            return 41;
            if(!strncpy(input+42,"halle",5))
            return 42;
            if(!strncpy(input+43,"allen",5))
            return 43;
            if(!strncpy(input+44,"lleng",5))
            return 44;
            if(!strncpy(input+45,"lenge",5))
            return 45;
            if(!strncpy(input+46,"enge}",5))
            return 46;
            if(!strncpy(input+47,"nge}",4))
            return 47;
            if(!strncpy(input+48,"ge}",3))
            return 48;
            if(!strncpy(input+49,"e}",2))
            return 49;
            if(!strncpy(input+50,"}",1))
            return 50;
    

    return 0;
}

int main(){
    char input[60];
    scanf("%60s",input);
    if(check(input))
       puts("Fail");
    else
       puts("Nice"); 
    return 0;
}
