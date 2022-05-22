#include "Qlearn.h" 
#include "functions.h"
#include "mazeEnv.h"


envOutput Q_step(action a){
    //similaire à maze_step mais avec le tableau des récompenses
    int done = 0;
    envOutput stepOut;

    if (a==up){
       state_row = max(0,state_row -1);
    }else if (a==down){
       state_row = min(rows-1,state_row +1);
    }else if (a==right){
       state_col = min(cols-1,state_col +1);
    }else if (a==left){
       state_col = max(0,state_col -1);
    }
    
    if((state_row == goal_row) && (state_col == goal_col)){
       done   = 1;
    }

    stepOut.reward = RewardTab[state_row][state_col]; // <--ici
    stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; 

   return stepOut;
}


void alloc_Q(void)
{       
        Q = malloc(cols*rows * sizeof(float*));
        int i;
        for (i = 0; i < cols*rows; ++i){
                Q[i] = malloc(number_actions * sizeof(float*));
        }
        int j;
        for (i = 0; i < cols*rows; ++i) {
                for (j = 0; j < number_actions ; ++j) {
                    Q[i][j] = 0;
                }
        }
}

void alloc_RewardTab(void)
{
        RewardTab = malloc(rows * sizeof(float*));
        int i;
        for (i = 0; i < rows; ++i){
                RewardTab[i] = malloc(cols * sizeof(float*));
        }
}


int nb_random(){

   /* Print 5 random numbers from 0 to 49 */
   return (rand() % 2);
   }
   
   


void init_RewardTab(void)
{
        alloc_RewardTab();

        int i, j;
        for (i = 0; i < rows; ++i) {
                for (j = 0; j < cols; ++j) {
                        if (maze[i][j] == '+') {
                                RewardTab[i][j] = -100;   //c'est un mur
                        } else if (maze[i][j] == 'g') {
                                RewardTab[i][j] = 100;    //l'objectif
                        } else {
                                RewardTab[i][j] =-0.06 ;  //c'est juste un pas
                        }
                }
        }
}




int trouve_max(int state, float ** Q) {
    //regarde autour de lui pour aller à la récompense max
    int reward_max =0;
    int i=1;
    while (i<4){
        if (Q[state][reward_max] < Q[state][i] ){
            reward_max=i;
        }
        i++;
    }
    return reward_max;
}

void chemin(){
    envOutput st;
    action at;
    init_state(&st);
    maze_reset();
    int i=0; //indice de dépassement
    while(i<cols*rows && st.done!=1 ){
        at=Qpolicy(st,Q,0.0);
        st = Q_step(at);
        maze[st.new_row][st.new_col]='.';
        i++;
    }
    maze[goal_row][goal_col]='g';
    maze[start_row][start_col]= 's';
    if(st.done!=1){
        printf(" pas assez d'étapes\n");
    }
    else{
        printf("\n");
    }
}

action Qpolicy(envOutput st, float **Q, float epsi){

  action at;
  int state=st.new_row*cols + st.new_col;
  if( ((rand() % 100)/100) < epsi )
    return (enum action)(rand() % number_actions);


  int a =trouve_max(state,Q);
 
  if (a==0){
    at=up;
  }else if(a==1){
    at=down;
  }else if(a==2){
    at=left;
  }else if(a==3){
    at=right;
  }

  return at;
}

void init_state(envOutput *stepOut){

    stepOut->reward = RewardTab[start_row][start_col];
    stepOut->done   = 0;
    stepOut->new_col = start_col;
    stepOut->new_row = start_row; 
}






void Qlearn(float gamma, float alpha){

    envOutput st1, st;  
    action at1,at;
    
    int k=0;
    float epsi=0.1;
    int max_s=100000;
    int I_max=1000;
    alloc_Q();
    alloc_RewardTab();
    init_RewardTab();
    
    for(int i=0;i<I_max;i++){
        init_state(&st);
        maze_reset();
        
        while(st.done!=1 ){
            //
            at=Qpolicy(st,Q,epsi);
            st1 = Q_step(at);
            at1 = Qpolicy(st1, Q, 0.0);
            Q[st.new_row*cols + st.new_col][at] += alpha*(st1.reward + gamma*Q[st1.new_row*cols + st1.new_col][at1] - Q[st.new_row*cols + st.new_col][at]);
            //
            st=st1;
            //
            k++;
            if (k>max_s){
                printf("besoin de plus d'étape\n");
                break;
            }
        }
        
        k=0;
    }

    chemin();

    
}

action SARSApolicy(){

}

void SARSA(float gamma, float alpha){

    envOutput st1, st;  
    action at1,at;
    
    int k=0;
    float epsi=0.1;
    int max_s=100000;
    int I_max=1000;
    alloc_Q();
    alloc_RewardTab();
    init_RewardTab();
    
    for(int i=0;i<I_max;i++){
        init_state(&st);
        maze_reset();
        
        while(st.done!=1 ){
            //
            at=Qpolicy(st,Q,epsi);
            st1 = Q_step(at);
            at1 = Qpolicy(st1, Q, 0.0);
            Q[st.new_row*cols + st.new_col][at] += alpha*(st1.reward + gamma*Q[st1.new_row*cols + st1.new_col][at1] - Q[st.new_row*cols + st.new_col][at]);
            //
            st=st1;
            //
            k++;
            if (k>max_s){
                printf("besoin de plus d'étape\n");
                break;
            }
        }
        
        k=0;
    }

    chemin();

    
}