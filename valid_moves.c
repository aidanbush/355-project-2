#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 8
#define MAX_COL 8
#define STONE_BLACK 'B'
#define STONE_WHITE 'W'
#define EMPTY_SPACE 'O'

typedef enum
{
  INIT_BLACK,
  INIT_WHITE,
  SEARCH_BLACK,
  SEARCH_WHITE,
} search_type;

/*Helper function to print a given state*/
int print_state(char **cur_state)
{
  int i, j;
  printf("\n   ");
  for (i = 0; i < MAX_ROW; i++)
  {
    printf("%d ", i);
  }
  printf("\n   ");
  for (i = 0; i < MAX_ROW; i++)
  {
    printf("- ");
  }
  printf("\n");
  for (i = 0; i < MAX_ROW; i++)
  {
    printf("%d |", i);
    for (j = 0; j < MAX_ROW; j++)
    {
      printf("%c ", cur_state[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  return 0;
}

/*Helper function to initialize a new state with the same layout as the current state*/
char **copy_state(char **cur_state)
{
  int i;
  char **new_state = malloc(sizeof(char *) * MAX_ROW);
  for (i = 0; i < MAX_ROW; i++)
  {
    new_state[i] = malloc(sizeof(char) * MAX_COL);
    strcpy(new_state[i], cur_state[i]);
  }
  return new_state;
}

/*creates an array of every possible state for the given move_set. The move_set is an integer
* that represents what we are searching for. 0-for the first move, 1-for black moves, 2-for white moves
*/
int valid_moves(char **cur_state, search_type move_set)
{
  int i, j, ind = 0;
  char search_char; //whether we are looking for the available moves for white or black
  char **temp_state = malloc(sizeof(char *) * MAX_ROW);
  for (i = 0; i < MAX_ROW; i++)
  {
    temp_state[i] = malloc(sizeof(char) * MAX_COL);
  }
  temp_state = copy_state(cur_state);

  //Restricted set of possible moves made for initial move
  if (move_set == INIT_BLACK)
  {
    temp_state = copy_state(cur_state);
    temp_state[3][3] = EMPTY_SPACE;
    temp_state = copy_state(cur_state);
    temp_state[4][4] = EMPTY_SPACE;
  }

  if (move_set == INIT_WHITE)
  {
    temp_state = copy_state(cur_state);
    temp_state[3][4] = EMPTY_SPACE;
    temp_state = copy_state(cur_state);
    temp_state[4][3] = EMPTY_SPACE;
  }

  if (move_set == SEARCH_BLACK)
  {
    search_char = STONE_BLACK;
  }
  else
  {
    search_char = STONE_WHITE;
  }
  //Search through state for possible moves based off search_char
  temp_state = copy_state(cur_state);
  for (i = 0; i < MAX_ROW; i++)
  {
    for (j = 0; j < MAX_COL; j++)
    {
      //Evaluate based on search_char
      if (temp_state[i][j] == search_char)
      {
        //check down
        if ((i + 2 < MAX_ROW))
        {
          if (temp_state[i + 1][j] != EMPTY_SPACE)
          {
            if (temp_state[i + 2][j] == EMPTY_SPACE)
            {
              printf("Jump Down From %d, %d:\n", i, j);
              temp_state[i + 2][j] = search_char;
              temp_state[i][j] = EMPTY_SPACE;
              temp_state[i + 1][j] = EMPTY_SPACE;
              print_state(temp_state); //ADD CHILD HERE
              if ((i + 4 < MAX_ROW))
              {
                if (temp_state[i + 3][j] != EMPTY_SPACE)
                {
                  if (temp_state[i + 4][j] == EMPTY_SPACE)
                  {
                    printf("Double Move Down From %d, %d:\n", i, j);
                    temp_state[i + 4][j] = search_char;
                    temp_state[i + 2][j] = EMPTY_SPACE;
                    temp_state[i + 3][j] = EMPTY_SPACE;
                    print_state(temp_state); //ADD CHILD HERE
                  }
                }
              }
              temp_state = copy_state(cur_state);
            }
          }
        }
        //check up
        if (i - 2 > 0)
        {
          if (temp_state[i - 1][j] != EMPTY_SPACE)
          {
            if (temp_state[i - 2][j] == EMPTY_SPACE)
            {
              printf("Jump Up From %d, %d:\n", i, j);
              temp_state[i - 2][j] = search_char;
              temp_state[i][j] = EMPTY_SPACE;
              temp_state[i - 1][j];
              print_state(temp_state); //ADD CHILD HERE
              if ((i - 4 > 0))
              {
                if (temp_state[i - 3][j] != EMPTY_SPACE)
                {
                  if (temp_state[i - 4][j] == EMPTY_SPACE)
                  {
                    printf("Double Move Up From %d, %d:\n", i, j);
                    temp_state[i - 4][j] = search_char;
                    temp_state[i - 2][j] = EMPTY_SPACE;
                    temp_state[i - 3][j] = EMPTY_SPACE;
                    print_state(temp_state); //ADD CHILD HERE
                  }
                }
              }
              temp_state = copy_state(cur_state);
            }
          }
        }

        //check right
        if (j + 2 < MAX_COL)
        {
          if (temp_state[i][j + 1] != EMPTY_SPACE)
          {
            if (temp_state[i][j + 2] == EMPTY_SPACE)
            {
              printf("Jump Right From %d, %d:\n", i, j);
              temp_state[i][j + 2] = search_char;
              temp_state[i][j] = EMPTY_SPACE;
              temp_state[i][j + 1] = EMPTY_SPACE;
              print_state(temp_state); //ADD CHILD HERE
              if ((j + 4 < MAX_COL))
              {
                if (temp_state[i][j + 3] != EMPTY_SPACE)
                {
                  if (temp_state[i][j + 4] == EMPTY_SPACE)
                  {
                    printf("Double Move Right From %d, %d:\n", i, j);
                    temp_state[i][j + 4] = search_char;
                    temp_state[i][j + 2] = EMPTY_SPACE;
                    temp_state[i][j + 3] = EMPTY_SPACE;
                    print_state(temp_state); //ADD CHILD HERE
                  }
                }
              }
              temp_state = copy_state(cur_state);
            }
          }
        }

        //check left
        if (j - 2 > 0)
        {
          if (temp_state[i][j - 1] != EMPTY_SPACE)
          {
            if (temp_state[i][j - 2] == EMPTY_SPACE)
            {
              printf("Jump Left From %d, %d:\n", i, j);
              temp_state[i][j - 2] = search_char;
              temp_state[i][j] = EMPTY_SPACE;
              temp_state[i][j - 1] = EMPTY_SPACE;
              print_state(temp_state); //ADD CHILD HERE
              if ((j - 4 > 0))
              {
                if (temp_state[i][j-3] != EMPTY_SPACE)
                {
                  if (temp_state[i][j-4] == EMPTY_SPACE)
                  {
                    printf("Double Move Left From %d, %d:\n", i, j);
                    temp_state[i][j - 4] = search_char;
                    temp_state[i][j - 2] = EMPTY_SPACE;
                    temp_state[i][j - 3] = EMPTY_SPACE;
                    print_state(temp_state); //ADD CHILD HERE
                  }
                }
              }
              temp_state = copy_state(cur_state);
            }
          }
        }
      }
    }
  }
  return 0;
}

//temporary main to make sure it handles the input properly
int main(void)
{
  char **state = malloc(sizeof(char *) * 8);
  int i;
  for (i = 0; i < 8; i++)
  {
    state[i] = malloc(sizeof(char) * 8);
  }
  state[0] = "BWBWBWBW";
  state[1] = "WOOBWBWB";
  state[2] = "BWBWBWBW";
  state[3] = "WBOBOOWB";
  state[4] = "BWBOBWOW";
  state[5] = "WBWBOBOB";
  state[6] = "BOBOBOBW";
  state[7] = "WBWBWBOB";

  valid_moves(state, STONE_WHITE);
}
