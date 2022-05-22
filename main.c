#include "Qlearn.h"
//#include "mazeEnv.h"
#include <time.h>




int main(){
   maze_make("maze3.txt");
   
   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   maze_render();
   
   //gamma , alpha
   Qlearn(0.3, 0.8);
   SARSA(0.3,0.8);
   return 0;
}

