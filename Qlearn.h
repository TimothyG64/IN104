#ifndef Q_LEARN_H
#define Q_LEARN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mazeEnv.h"

float **RewardTab;
float **Q;


envOutput Q_step(action a); 


void alloc_RewardTab(void);

void alloc_Q(void);


void init_RewardTab(void);

action trouve_max(int state, float ** Q);

action Qpolicy(envOutput st, float **Q, float epsi);

action SARSApolicy(envOutput st, float **Q);

void init_state(envOutput *stepOut);

void chemin(void);

void cheminSARSA(void);

void chemin2(void);

void Qlearn(float alpha, float gamma);

void SARSA(float alpha, float gamma);

int nb_random(void);


#endif
