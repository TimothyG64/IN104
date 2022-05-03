/*
 * @Author: your name
 * @Date: 2022-04-05 16:58:37
 * @LastEditTime: 2022-05-03 16:37:03
 * @LastEditors: Zhou Yanyu（周妍妤） earthazyy@hotmail.com
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \CMaze-main\qlearning.c
 */

#include <stdio.h>
#include "mazeEnv.h"
#include "mazeEnv.c"
#include "functions.c"
#include "functions.h"
// Exploration factor
#define double alpha = 0.1; // learning rate
#define double epsilon = 0.1 ; 
#define double gamma = 0.9 ; // discount factor
#define double visited_mark = 0.8; // Cells visited by the rat will be painted by gray 0.8
#define double rat_mark = 0.5; //# The current rat cell will be painteg by gray 0.5

/* maze is a 2d array of character, there are 5 types of cells:
unknown, wall, known, goal, crumb
We have 4 action:
0 - up,
1 - down,
2 - left,
3 - right,
4 - number_actions 
Our rewards is floating points ranging from -1.0 to 1.0
Each move from one state to the next state will be rewarded by a positive or negative amount
Each move form one cell to an adjacent cell will cost the rat -0.04 points
The maximal reward is 1.0 at the goal cell
An attempt to a wall cell will cost -0.75 points and the action will not be executed
An attempt to move outside the maze boundaries costs -0.8
An attempt to crumb cells costs -0.25 and will not be executed
To avoid infinite loops, the game is ended once the total reward is below the threshold -0.5*mazesize

*/
//For each point on the map, return the reward
int RNG (int largestValue){
    int k = rand() % (largestValue+1);
    return k;
}

double reward(int row, int col){
    double points;
    switch (maze[row][col]){
    case '+':
        points = -1.5;
        break;

    case '.':
        points = -0.25;
        break;

    case 'g':
        points = 1000;
        break;
    
    default:
        points = -0.04;
        break;
    }

    return points;
}

//FInd the best action for a given state
int Max_action(int row, int col){
    double max_qvalue = qtable[ rows * row + col][0];
    int temp_action = 0;

    for(int i = 0; i < 4; ++i){
        if (qtable[ 4* row + col][i] > max_qvalue){
            temp_action = i;
            max_qvalue = qtable[ rows * row + col][i];
        }
    }
    return temp_action;
}

//determine the qvalue for a (state,action)
double qfunction(int row, int col, int action){
    double qvalue;
    int state = rows * row + col;

    qvalue = qtable [state,action] + epsilon * (reward(row,col) + gamma *Max_action(row,col) - qtable [state , action]); 

    return qvalue;
}


int qlearning(int row, int col){

}

int main(){
    double **qtable = calloc(rows * cols,sizeof(double*));
    for (int i=1; i < (rows * cols); ++i){
        qtable[i] = calloc(number_actions, sizeof(double*));
    }

    maze_reset();
    maze_make("maze.txt");
    init_visited();
    alloc_qtable();
    int visited[rows][cols];



    int rowCounter = 0; 
    while(maze[start_row][start_col] != 'g'){
        //indicate the current location
        maze[state_row][state_col] = 'x';

        switch(maze[state_row][state_col]){
            
        }
    }


   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   maze_render();
   qlearning(start_row,start_col);
   add_crumbs();
   maze_render();
   return 0;
}