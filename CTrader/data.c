#include "data.h" 
/*
void collect_data(char* file_name){
     char c;
     char N_s[3] ={'\0'};
     int N_i = 0;
     int swap = 0;

     FILE* file = fopen(file_name, "r");

     if (file) {
         // lire la premiere ligne avant EOF 
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

     // convertir le string en nombre 
     int N = atoi(N_s);
     fclose(file);
} 
*/
void collect_data(char *filename){
       read_csv(7,1280,char *filename, data);
}


void read_csv(int row, int col, char *filename, double **data){
	FILE *file;
	file = fopen(filename, "r");

	int i = 0;
    char line[4098];
	while (fgets(line, 4098, file) && (i < row))
    {
    	// double row[ssParams->nreal + 1];
        char* tmp = strdup(line);

	    int j = 0;
	    const char* tok;
	    for (tok = strtok(line, ","); tok && *tok; j++, tok = strtok(NULL, ",\n"))
	    {
	        data[i][j] = atof(tok);
	        printf("%f\t", data[i][j]);
	    }
	    printf("\n");

        free(tmp);
        i++;
    }
}