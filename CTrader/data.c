#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h" 

void collect_data(char* file_name){
     char c;
     char N_s[3] ={'\0'};
     int N_i = 0;
     int swap = 0;

     FILE* file = fopen(file_name, "r");

     if (file) {
         /* lire la premiere ligne avant EOF */
         while( (c=getc(file)) != EOF) {
               if(c== '\n'){
                      break;
               } else if (c==',') {
                      swap = 1;
               } else if (!swap) {
                      N_s[N_i]=c;
                      N_i++;
               }
         }
     }

     /* convertir le string en nombre */
     int N = atoi(N_s);
     fclose(file);
}