#ifndef Q_LEARN_H
#define Q_LEARN_H

#include <stdio.h>
#include <stdlib.h>
//#include "mazeEnv.h"

char** maze;
float **RewardTab;
float **Q;
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

// MAZZZZZZZZZZZZZZZZZZZE   ----- A supprimer
enum action{
     up,
     down,
     left,
     right,
     number_actions 
};
 
typedef enum action action ;

struct envOutput{
  int new_col;
  int new_row;
  int reward;
  int done;

};

typedef struct envOutput envOutput;

void alloc_maze();

void maze_make(char* );

void maze_render(); 

void maze_reset();

envOutput maze_step(action a); 

// FIN MAZZZZZZZZZZZZZZZZZZZZZE

void alloc_RewardTab(void);

void alloc_Q(void);


void init_RewardTab(void);

int trouve_max(int state, float ** Q);

action Qpolicy(envOutput st, float **Q, float epsi);

void init_state(envOutput *stepOut);

void chemin(void);

void Qlearn(float alpha, float gamma);

int nb_random(void);


#endif
