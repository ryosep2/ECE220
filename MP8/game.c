/*
  -----------------------------------------------------------------------------------
    Tony Xu (tonyx2)
    MP8
    Partners: Ryan Yoseph (ryosep2), Ishaan Attri (iattri2)

    In this program, we were instruted to implement the famous 2048 game using pointers, data structures of current and future game boards,
    and various helper methods. We initialized the board by storing rows, columns, and the score of the game in different pointers.
    Afterwards, we set all the cells in the board to be empty, and created a specific memory location for each tile. When the game started,
    we instruct the user to input dimensions of board and they would then proceed to use the keys w,a,s,d for the up, left, down, and right
    functions respectively. The functions to move the cells in the game were very similar, but the only difference between most of them were the
    termination conditions and how it was iterated. Each time a cell was moved the game would check if there were any legal moves left by first
    checking if there were any empty spaces and then would check if there were any merges available. If no entry would work, the game would end.
    You can also quit the game by pressing q as well.

    This is the function of our code.

    Thank you. 

  ------------------------------------------------------------------------------------
*/


#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

    mygame->rows=rows;
    mygame->cols=cols;
    mygame->score=0;

    int i;
    for(i=0;i<rows*cols;i++)
      mygame->cells[i]=-1;



    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));


  (*_cur_game_ptr)->rows=new_rows;
  (*_cur_game_ptr)->cols=new_cols;
  (*_cur_game_ptr)->score=0;

  int i;
  for(i=0;i<new_rows*new_cols;i++)
    (*_cur_game_ptr)->cells[i]=-1;

	return ;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);

    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{

  int cols = cur_game->cols;


  if(row >= cur_game->rows || row < 0 || col >= cur_game->cols || col < 0)
    return NULL;
  else{
    cell *ptr = &(cur_game->cells[cols*row + col]);
    return ptr;
  }
}


int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
  int n;
  int m;
  int row;                                                                //initialize loop variables
	int checkMove = 0;                                                      //initialize return variable
	int rows = (*cur_game).rows;                                            //access variable rows from the cur_game struct
	int cols = (*cur_game).cols;                                            //access variable cols from the cur_game struct

	for (n = 0; n < cols; n++) {
    					                                                            //go through all the columns
		for (m = 0; m < rows; m++) {
      					                                                          //go through all the rows
			if (*get_cell(cur_game, m, n) != -1) {								              //checking if the cell is not empty

        int prevCombinedCell = -2;                                        //set prevCombinedCell to negative 2 so it never points to the row above any cell, to start with

				for (row = 0; row < m; row++) {											              //traverse through a specific column
					if (*get_cell(cur_game, row, n) == -1) {						            //traverse through current column to find empty cells
						*get_cell(cur_game, row, n) = *get_cell(cur_game, m, n);		  //Once an empty cell is found, replace that cell with value at [m,n]
						*get_cell(cur_game, m, n) = -1;										           	//set the value of the cell that was just moved to empty (-1)
						checkMove = 1;															                  //this move is now valid, set return value to 1
						break;                                                        //The break commands ensures that we do not add multiple tiles in one iteration
					}
				}

				if (prevCombinedCell  != (row - 1)) {                             // if the tile/cell above the tile that has currently been slid up is also the
                                                                          //previously combined cell, then we cannot combine these two cells, otherwise then the prev combined cell would be merging twice
					if (get_cell(cur_game, row - 1, n) != NULL) {                   //here we also check if the tile above is not null or or empty
						if (*get_cell(cur_game, row - 1, n) == -1) {							               //if cell empty or null,  skip merging process
							break;
						}
						if (*get_cell(cur_game, row - 1, n) == *get_cell(cur_game, row, n)) {		//check if both tiles have same value
							*get_cell(cur_game, row - 1, n) = (*get_cell(cur_game, row, n)) * 2;		//multiply cell by 2 to combine
							*get_cell(cur_game, row, n) = -1;								                  		//make the bottom cell empty
							prevCombinedCell = row - 1;										                       	//set prevCombinedCell row value to the top cell's row (row-1)
							(*cur_game).score = (*cur_game).score + *get_cell(cur_game, row - 1, n);	//update game score
							checkMove = 1;															                        //this move is now valid, set return value to 1
						}
					}
				}
			}
		}
	}

    return checkMove;
};

int move_s(game * cur_game) //slide down
/*
    this method follows the same logic as the move_w method
    with slight adjustments, to account for the change in direction.
    these changes are as follows:
      -the second column loop starts at the bottom of the column and goes up (the opposite of how it is in move_w)
      -the cell that we are looking to merge with will be the one below (we looked at the one above for move_w)


*/
{
  int n;
  int m;
  int row;
  int checkMove = 0;
  int rows = (*cur_game).rows;
  int cols = (*cur_game).cols;
  int prevCombinedCell = -2;


for (n = 0; n < cols; n++) {

  for (m = rows - 1; m >= 0; m--) {

    if (*get_cell(cur_game, m, n) != -1) {


      for (row = rows - 1; row > m; row--) {
        if (*get_cell(cur_game, row, n) == -1) {
          *get_cell(cur_game, row, n) = *get_cell(cur_game, m, n);
          *get_cell(cur_game, m, n) = -1;
          checkMove = 1;
          break;
        }
      }

      if (prevCombinedCell != (row + 1)) {
        if (get_cell(cur_game, row + 1, n) != NULL) {
          if (*get_cell(cur_game, row + 1, n) == -1) {
            break;
          }
          if (*get_cell(cur_game, row + 1, n) == *get_cell(cur_game, row, n)) {
            *get_cell(cur_game, row + 1, n) = (*get_cell(cur_game, row, n)) * 2;
            *get_cell(cur_game, row, n) = -1;
            prevCombinedCell = row + 1;
            (*cur_game).score = (*cur_game).score + *get_cell(cur_game, row + 1, n);
            checkMove = 1;
          }
        }
      }
    }
  }
}

return checkMove;
};

int move_a(game * cur_game) //slide left
/*
    this method follows the same logic as the move_w method
    with slight adjustments, to account for the change in direction.
    these changes are as follows:
      -the second column loop is replaced with a second row loop
      -the second row loop starts from the left and traverses right
      -we traverse through row by row instead of column by column
      -the cell that we are looking to merge with will be the one to the left (we looked at the one above for move_w)


*/
{
  int n;
  int m;
  int col;
  int checkMove = 0;
  int rows = (*cur_game).rows;
  int cols = (*cur_game).cols;
  int prevCombinedCell = -2;


for (m = 0; m < rows; m++) {

  for (n = 0; n < cols; n++) {

    if (*get_cell(cur_game, m, n) != -1) {

      for (col = 0; col < n; col++) {
        if (*get_cell(cur_game, m, col) == -1) {
          *get_cell(cur_game, m, col) = *get_cell(cur_game, m, n);
          *get_cell(cur_game, m, n) = -1;
          checkMove = 1;
          break;
        }
      }

      if (prevCombinedCell != (col - 1)) {
        if (get_cell(cur_game, m, col - 1) != NULL) {
          if (*get_cell(cur_game, m, col - 1) == -1) {
            break;
          }
          if (*get_cell(cur_game, m, col - 1) == *get_cell(cur_game, m, col)) {
            *get_cell(cur_game, m, col - 1) = *get_cell(cur_game, m, col) * 2;
            *get_cell(cur_game, m, col) = -1;
            prevCombinedCell = col - 1;
            (*cur_game).score = (*cur_game).score + *get_cell(cur_game, m, col - 1);
            checkMove = 1;
          }
        }
      }
    }
  }
}

  return checkMove;
};

int move_d(game * cur_game) //slide right
/*
    this method follows the same logic as the move_w method
    with slight adjustments, to account for the change in direction.
    these changes are as follows:
      -the second column loop is replaced with a second row loop
      -the second row loop starts from the right and traverse left (opposite of move_a)
      -we traverse through row by row instead of column by column
      -the cell that we are looking to merge with will be the one to the right (we looked at the one above for move_w)


*/
{
  int n;
  int m;
  int col;
  int checkMove = 0;
  int rows = (*cur_game).rows;
  int cols = (*cur_game).cols;
  int prevCombinedCell = -2;


	for (m = 0; m < rows; m++) {

		for (n = cols - 1; n >= 0; n--) {

			if (*get_cell(cur_game, m, n) != -1) {

				for (col = cols - 1; col > n; col--) {
					if (*get_cell(cur_game, m, col) == -1) {
						*get_cell(cur_game, m, col) = *get_cell(cur_game, m, n);
						*get_cell(cur_game, m, n) = -1;
						checkMove = 1;
						break;
					}
				}

				if (prevCombinedCell != (col + 1)) {
					if (get_cell(cur_game, m, col + 1) != NULL) {
						if (*get_cell(cur_game, m, col + 1) == -1) {
							break;
						}
						if (*get_cell(cur_game, m, col + 1) == *get_cell(cur_game, m, col)) {
							*get_cell(cur_game, m, col + 1) = *get_cell(cur_game, m, col) * 2;
							*get_cell(cur_game, m, col) = -1;
							prevCombinedCell = col + 1;
							(*cur_game).score = (*cur_game).score + *get_cell(cur_game, m, col + 1);
							checkMove = 1;
						}
					}
				}
			}
		}
	}

	return checkMove;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
  int m, n;
  int isLegal = 0;
  int rows = (*cur_game).rows;
  int cols = (*cur_game).cols;

for (m = 0; m < rows; m++) {
																						//go through the game board
  for (n = 0; n < cols; n++) {


    if (*get_cell(cur_game, m, n) == -1) {										//if there is atleast one empty cell in the board, there can be a valid move made
      isLegal = 1;
      break;
    }

    //series of checks, too see if atleast one of the cells neighbors is not null and is the same value as the cell, meaning some valid move can still be made
    if ((get_cell(cur_game, m - 1, n) != NULL) && (*get_cell(cur_game, m, n) == *get_cell(cur_game, m - 1, n))) {
      isLegal = 1;
    }
    else if ((get_cell(cur_game, m, n - 1) != NULL) && (*get_cell(cur_game, m, n) == *get_cell(cur_game, m, n - 1))) {
      isLegal = 1;
    }
    else if ((get_cell(cur_game, m, n + 1) != NULL) && (*get_cell(cur_game, m, n) == *get_cell(cur_game, m, n + 1))) {
      isLegal = 1;
    }
    else if ((get_cell(cur_game, m + 1, n) != NULL) && (*get_cell(cur_game, m, n) == *get_cell(cur_game, m + 1, n))) {
      isLegal = 1;
    }

  }
  if(isLegal == 1)        // if we have already found atleast one valid move, we need not continue searching
    break;
}

return isLegal;

}





/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
