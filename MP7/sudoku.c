#include "sudoku.h"

/*
-------------------------------------------------------------------------------------------------
    Ryan Yoseph (ryosep2)
    MP7
    Partners: Ishaan Attri (iattri2) , Tony Xu (tonyx2)

    In this program, we were instructed to implement a sudoku board solver, using recursion and various helper methods.
    We had four helper methods, three that checked if a certain entry already existed with and row, column, or 3x3 block,
    and then one method that used those three methods to check if an entry was valid for a given position.
    In the solve_sudoku method, we used backtracking recursion by going through all possible entries for a given
    empty cell and seeing if the board with the new entry would be completed in future iterations of the method call.
    If no entry would work, then we left the cell blank and returned false, this indicates to previous iterations that
    the entry that was put in the cell in the previous generation was invalid, and so on and so forth.

-------------------------------------------------------------------------------------------------
*/



// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int x;

  for(x = 0; x < 9; x++){           /*simply traverse through array  to see if val exists*/

    if(sudoku[i][x] == val)
      return 1;
  }

  return 0;

}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  int x;

  for(x = 0; x < 9; x++){           /*simply traverse through array  to see if val exists*/

    if(sudoku[x][j] == val)
      return 1;
  }

  return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  int x, y;
  int x_offset, y_offset;

  x_offset = j/3;                                   /*first divide the given coordinates by 3 to indicate what 'block' they are in, here we use integer division to our advantage*/
  y_offset = i/3;
  x_offset = 3*x_offset;                            /*mutliply the result in the offsets by 3, to get the starting (top left)  coordinates of the proper block*/
  y_offset = 3*y_offset;

  for(y = 0; y < 3; y++)                              /*traverse through the block and see if the value exists*/
    for(int x = 0; x < 3; x++)
      if( sudoku[y + y_offset][x + x_offset] == val)        /*add the offsets to index of array while traversing through block*/
        return 1;


  return 0;


}

// Function: is_val_valid
// Return true if the val can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  int count = 0;

  count += is_val_in_3x3_zone(val, i, j, sudoku);     /*call all three 'valid' type methods, add their respective return values al to count*/
  count += is_val_in_col(val, j, sudoku);
  count += is_val_in_row(val, i, sudoku);


  if(count == 0)                                      /* count should be zero if all the 'valid' methods returned 0, meaning the entry specified is valid*/
    return 1;
  else
    return 0;

}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  int i, j, num;
  int a, b;
  int filled = 1;



  for(i = 0; i < 9; i++){
    for(j = 0; j < 9; j++){     /*nested for loops to traverse through array*/
      if(sudoku[i][j] == 0){
        filled = 0;
        a = i;                  /*if an empty cell is found, save the location for later into a,b, set filled to false, and break out of loop*/
        b = j;
        break;
      }
    }
  }

    if (filled == 1)          /*return true if array is already filled completely*/
      return 1;


    for(num = 1; num <= 9; num++){            /*iterate through possible entries into empty cell*/

//    printf("&&&&&&&&&&&&&&&&&&&& i : %d j : %d &&&&&&&&&&&&&&&&&&&&&&&\n", a, b);  /*used this line for debugging and seeing the code run visually*/


      if (is_val_valid(num, a, b, sudoku) == 1) {           /*if entry is a valid entry, then fill cell with entry*/
        sudoku[a][b] = num;

        if (solve_sudoku(sudoku))                           /*check if the sudoko board can be solved with this entry in this cell by calling another instance*/
          return 1;                                         /*of solve_sudoku with the cell in question updated with the new entry*/
                                                            /*if board can be solved, return 1, other wise leave the cell empty*/

        sudoku[a][b] = 0;
      }

    }
    return 0;                                               /*if the cell is left empty, return false after, this indicates to previous calls of solve_sudoku*/
                                                            /* that the board cannot be solved with the previous entry in the cell of the board in the  previuos instance of the method*/
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
