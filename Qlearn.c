#include "Qlearn.h" 
#include "functions.h"
#include "mazeEnv.h"
#include <math.h>


envOutput Q_step(action a){
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

    stepOut.reward = RewardTab[state_row][state_col]; //changed here
    stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; 

   return stepOut;
}

void add_crumbs(){
     int k =0;
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  maze[i][j] = '.';
                  k++;
              }
          }
     }
     maze[start_row][start_col]= 's';
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

void init_state(envOutput *stepOut){
    stepOut->reward = RewardTab[start_row][start_col];
    stepOut->done   = 0;
    stepOut->new_col = start_col;
    stepOut->new_row = start_row; 
}

void alloc_RewardTab(void)
{
        RewardTab = malloc(rows * sizeof(float*));
        int i;
        for (i = 0; i < rows; ++i){
                RewardTab[i] = malloc(cols * sizeof(float*));
        }
}


void init_RewardQ(void)
{
        alloc_RewardTab();

        int i, j;
        for (i = 0; i < rows; ++i) {
                for (j = 0; j < cols; ++j) {
                        if (maze[i][j] == '+') {
                                RewardTab[i][j] = -1000;   //c'est un mur
                        } else if (maze[i][j] == 'g') {
                                RewardTab[i][j] = 100;   
                        } else {
                                RewardTab[i][j] =- 0.04;  //c'est juste un pas
                        }
                }
        }
}

void init_RewardSARSA(void)
{
        alloc_RewardTab();

        int i, j;
        for (i = 0; i < rows; ++i) {
                for (j = 0; j < cols; ++j) {
                        if (maze[i][j] == '+') {
                                RewardTab[i][j] = -1000;   //c'est un mur
                        } else if (maze[i][j] == 'g') {
                                RewardTab[i][j] = 100;   
                        } else {
                                RewardTab[i][j] =-1 ;  //c'est juste un pas
                        }
                }
        }
}



action trouve_max(int state, float ** Q) {
    action at;
    int reward_max =0;
    int i=1;
    while (i<4){
        if (Q[state][reward_max] < Q[state][i] ){
            reward_max=i;
        }
        i++;
    }
    if (reward_max==0){
        at=up;
    }else if(reward_max==1){
        at=down;
    }else if(reward_max==2){
        at=left;
    }else if(reward_max==3){
        at=right;
    }
    return(at);
}



void chemin(){
    envOutput s; action a;
    init_state(&s);
    maze_reset();
    
    
    init_visited();
    int i=0; //indice de dépassement
    while(i<cols*rows && s.done!=1 ){
        int state=s.new_row*cols + s.new_col;
        a = trouve_max(state, Q);
        s = maze_step(a);
        visited[s.new_row][s.new_col] = crumb;
        //printf("%d %d \n",s.new_row,s.new_col);
        i++;
    }
    if(s.done!=1){
        printf(" Erreur\n");
    }
    add_crumbs();
    maze[goal_row][goal_col]='g';
    maze[start_row][start_col]= 's';
    maze_render();
}



action Epolicy(envOutput st, float **Q, float epsi){ // méthode epsi-Greedy

  action at;
  int state=st.new_row*cols + st.new_col;
  if( ((rand() % 100)/100) < epsi )  
    return (enum action)(rand() % number_actions);


  at =trouve_max(state,Q);
 
  return at;
}



action Boltzpolicy(envOutput st, float **Q){
  action at;

  int state=st.new_row*cols + st.new_col;
  // Botzmann exploration
  double p0 = exp(Q[state][0]);double p1 = exp(Q[state][1]);double p2 = exp(Q[state][2]);double p3 = exp(Q[state][3]);
  
  double pt = p0+p1+p2+p3; 
  double x = (rand() % 1001 +1)/1000;
  x = x*(int)pt;
  //printf("%f %f \n", x, pt);
  if (x<p0)
  {
      at=up;
      //printf("up \n");
  }else if(x<p1+p0){
      at=down;
      //printf("down \n");
  }else if(x<p2+p1+p0){
      at=left;
      //printf("left \n");
  }else{
      at=right;
      //printf("right \n");
  }
  return at;
}



void Qlearn(float gamma, float alpha){

    envOutput st1, st;  
    action mat,at;
    
    int k=0;
    float epsi=0.1;
    int max_s=1000000;
    int I_max=1000;
    alloc_visited();
    init_visited();
    alloc_Q();
    alloc_RewardTab();
    init_RewardQ();
    
    for(int i=0;i<I_max;i++){
        init_state(&st);
        maze_reset();
        
        while(st.done!=1 ){
            //
            at=Epolicy(st,Q,epsi);
            st1 = Q_step(at);
            mat = Epolicy(st1, Q, 0.0); //max at
            int state = st.new_row*cols + st.new_col; int state1 = st1.new_row*cols + st1.new_col;
            Q[state][at] += alpha*(st1.reward + gamma*Q[state1][mat] - Q[state][at]);
            //
            st=st1;
            //
            k++;
            if (k>max_s){
                printf("besoin de plus d'étape\n");
                break;

            //printf("%d, %d \n",);
            }
        }
        
        k=0;
    }
    
    chemin();
    free(Q);free(RewardTab);free(visited);
    
}



void SARSA(float gamma, float alpha){

    envOutput st1, st;  
    action at1,at;
    
    int k=0;
    int max_s=10000;
    int I_max=1000;
    alloc_Q();
    alloc_RewardTab();
    init_RewardSARSA();
    
    for(int i=0;i<I_max;i++){
        init_state(&st);
        at=Epolicy(st,Q,0.0); //max a
        maze_reset();
        
        while(st.done!=1 ){
            st1 = Q_step(at);
            at1 = Epolicy(st1, Q,0.0);
            int state = st.new_row*cols + st.new_col; int state1 = st1.new_row*cols + st1.new_col;
            Q[state][at] += alpha*(st1.reward + gamma*Q[state1][at1] - Q[state][at]);
            // si on n'arrive pas dans un mur
            if(maze[st1.new_row][st1.new_col]!='+'){
                st=st1; //on avance
                at =at1;
            }
            
            k++;
            if (k>max_s){
                //printf("besoin de plus d'étape\n");
                break;
            }
        }
        
        k=0;
    }
    

    chemin();

    free(Q);free(RewardTab);free(visited);
    
}