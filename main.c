#include "Qlearn.h"
//#include "mazeEnv.h"
#include <time.h>




int main(){
   maze_make("maze.txt");
   
   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   maze_render();
   
   //gamma , alpha
   Qlearn(0.1, 0.9);
   return 0;
}

