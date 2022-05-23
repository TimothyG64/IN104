#include "Qlearn.h"
#include "mazeEnv.h"
#include <time.h>




int main(){
   int choix;
   maze_make("maze.txt");
   
   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   maze_render();
   
   printf("please choose between : \n \t -Qlearning 1 \n \t -SARSA 2 \n \t -Compare 3 \n");
   scanf("%d",&choix);
   //gamma , alpha
   clock_t start, end;
   double cpu_time;
   if (choix == 1)
   {
      start = clock();
      Qlearn(0.3, 0.8);
      end= clock();
      cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("Chrono Qlearning : %f \n", cpu_time );
   }else if(choix == 2){
      start = clock();
      SARSA(0.8,0.3);
      end= clock();
      cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("Chrono SARSA : %f \n", cpu_time);
   }else {
      start = clock();
      Qlearn(0.3,0.8);
      end= clock();
      cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
      SARSA(0.8,0.8);
      clock_t end1= clock();
      double cpu_time1 = ((double) (end1 - end)) / CLOCKS_PER_SEC;
      printf("Chrono Qlearning : %f \n", cpu_time);
      printf("Chrono SARSA : %f \n", cpu_time1);
   }
   free(maze);
   return 0;
}

