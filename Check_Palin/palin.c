#include "palin.h"
#include <stdio.h>
#include <string.h>

int isPalin(char str[]){
    int start = 0;
    int end = strlen(str) -1 ;

    if (str[end] == '\n'){
        str[end] = '\0';
        end--;
    }

    while(start<end){
        if(str[start] != str[end]){
            return 0;

        }
        start ++;
        end --;
    }
    return 1;
}