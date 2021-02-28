/*
			Ryan Yoseph (ryosep2) 
			MP6
			Partner: Ishaan Attri (iattri2)

			In this program we were given three functions to implement that would handle the mechanics of the game of life simulation.
				countLiveNeighbor was responsible for finding the number of live neighbors of any given cell. The approach was pretty straightforward for
			any cell that was in the middle of the array. We had to make a few checks to handle the edge cases  (in order to avoid checking a neighbor that doesnt exist).
			We did this by running two for loops, each going from -1 to 1, which represents the shift/distance away from the cell at hand that the nieghbor is, then checking if the
			current neighbor was out of bounds, or was the cell itself in which case we also do not check.
				In updateBoard, we first made an array to store the number of liveNeighbors for each cell, and then updated the board. this prevented us from making the
			mistake of dynamically updating the board, becuase the number of liveNeighbors would change as we updated the board, but this is not desired as each generation
			of the board should be reliant on the previous generation only.
			Finally in aliveStable we made two clones of the board to avoid changing the actual board, then ran updateBoard on one instance of the clones, then compared the
			old clone with the updated clone. 

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count num neighbors.
 * col: the col of the cell that needs to count num neighbors.
 * Output:
 * return the number of num neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

		int num = 0;
		int h = boardRowSize;
		int w = boardColSize;
		int i, j;


		for(i = -1; i < 2; i++){																		/*nested for loops to go through all 8 possible liveNeighbors*/
			for(j = -1; j < 2; j++){

				if(i == 0 && j == 0)																		/*do not check if you are at the index in question*/
					continue;

				if(row+i < 0 || row+i >= h || col+j < 0 || col+j >= w)		/*if neighbor is actually out of bounds, do not check*/
					continue;
				else if(board[w*(row+i) + col + j] == 1)								/*if neighbor exists and is alive, increase count*/
					num++;

			}

		}

		return num;

}
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {


		int n = boardRowSize*boardColSize;
		int w = boardColSize;
		int liveNeighbors[n];
		int i,j;



		for( i = 0; i < boardRowSize; i++)							/*for loops to traverse through board and fill liveNeighbors with appropriate data*/
			for(j = 0; j < boardColSize; j++ )
				liveNeighbors[i*w+j] = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);




		for( i = 0; i < boardRowSize; i++){
			for(j = 0; j < boardColSize; j++ ){							/*traverse through board to update each cell*/

				if(board[i*w+j] == 1){										/*conditional chunk to reflect logic provided by rules of the game, decides what happens to each cell*/

					if(liveNeighbors[i*w+j] < 2 || liveNeighbors[i*w+j] > 3)
						board[i*w+j] = 0;

				}
				else if(board[i*w+j] == 0){

					if(liveNeighbors[i*w+j] == 3)
						board[i*w+j] = 1;

				}

			}
		}


}



/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){

	int n = boardRowSize*boardColSize;
	int futureBoard[n];
	int oldBoard[n];
	int i;

	for(i = 0; i < n; i++){									/*make two clones of the board to avoid changing the actual board*/
		oldBoard[i] = board[i];
		futureBoard[i] = board[i];
	}

	updateBoard(futureBoard, boardRowSize, boardColSize);			/*run an update board on one of the clones*/

	for(i = 0; i < n; i++){
		if(oldBoard[i] != futureBoard[i])											/*go through and check for any discrepencies between old clone and next generation clone*/
			return 0;																						/*if at any point there is a discrepency then return 0*/
	}

	return 1;																								/*at this point in the code there must not be any differences, so return 1*/

}
