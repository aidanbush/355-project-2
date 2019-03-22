#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Helper function to print a given state*/
int print_state(char**cur_state){
  int i, j;
  for(i=0; i < 8;i++){
    for(j=0; j < 8; j++){
      printf("%c", cur_state[i][j]);
    }
    printf("\n");
  }
  return 0;
}

/*Helper function to initialize a new state with the same layout as the current state*/
char** copy_state(char** cur_state){
  int i;
  char** new_state = malloc(sizeof(char*)*8);
  for(i=0;i<8;i++){
    new_state[i] = malloc(sizeof(char)* 8);
    strcpy(new_state[i],cur_state[i]);
  }
  return new_state;
}



char*** valid_moves(char** cur_state, int move_set){
  int i,j;
  char search_char; //whether we are looking for the available moves for white or black
  char** temp_state = malloc(sizeof(char*)*8);
  for(i=0;i<8;i++){
    temp_state[i] = malloc(sizeof(char)* 8);
  }
  temp_state = copy_state(cur_state);
  char*** valid_states = calloc(4,sizeof(temp_state));
  if(valid_states == NULL){
    printf("Error in allocation");
  }
  //Restricted set of possible moves made for initial move
  if (move_set == 0){
    temp_state[0][0] = 'O';
    valid_states[0] = temp_state;

    temp_state = copy_state(cur_state);
    temp_state[3][3] = 'O';
    valid_states[1] = temp_state;

    temp_state = copy_state(cur_state);
    temp_state[4][4] = 'O';
    valid_states[2] = temp_state;

    temp_state = copy_state(cur_state);
    temp_state[7][7] = 'O';
    valid_states[3] = temp_state;
  }

  if(move_set == 1){
    search_char = 'B';
  }
  else{
    search_char='W';
  }

  //Search through state for possible moves based off search_char


  
  printf("Take first B:\n");
  print_state(valid_states[0]);

  printf("Take second B:\n");
  print_state(valid_states[1]);

  printf("Take third B:\n");
  print_state(valid_states[2]);

  printf("Take fourth B:\n");
  print_state(valid_states[3]);
  return 0;
}

//temporary main to make sure it handles the input properly
int main(void){
  char **state = malloc(sizeof(char*)*8);
  int i;
  for(i=0; i<8;i++){
    state[i] = malloc(sizeof(char)*8);
  }
  state[0] = "BWBWBWBW";
  state[1] = "WBWBWBWB";
  state[2] = "BWBWBWBW";
  state[3] = "WBWBWBWB";
  state[4] = "BWBWBWBW";
  state[5] = "WBWBWBWB";
  state[6] = "BWBWBWBW";
  state[7] = "WBWBWBWB";
  valid_moves(state, 0);
}
