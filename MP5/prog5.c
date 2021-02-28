/*Ryan Yoseph (ryosep2)*/
/*
 	Introduction Paragraph:
 		In this program we were intructed to write three methods that work together in main.c to implement a version 
 	of the game "Mastermind". 
		In set_seed, we implemented the srand() function to generate a random seed. We used sscanf 
	to read the integer from the seed_str[] to put into srand(), while throwing an exception if the input was invalid.
		In start_game we simply initialized the solution that the user is trying to crack by using the rand() function, 
	and also set the guess_number to zero.
		In the make_guess method, we set up two arrays: one that would store how many perfect matches were entered in one guess
		and another that stored the value of the solution. First, the user would input his 4 integer guess between 1-7, 
		which were stored in w, x, y, z, respectively, by using sscanf function. The code that we wrote used pointers to each respective
		guess and checked if it was a perfect match to the solution set. Once the guess was checked for all perfect matches, we would then 
		see if there were any mismatched guesses. This means that we inputted a number for our guess that was in the solution set but was not 
		in the correct position. After each guess, the computer would tell us how many perfect and mismatched matches we inputted, and also what 
		guess number we were on. After 5 guesses, the program terminates. If the user gets the right order and values of the solution in his guess,
		then you won the game and the program terminates. That is all. Thank you. Good night. 

		Partners:
			Tony Xu (tonyx2)
			Ishaan Attri (iattri2)
 */


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"



static int guess_number; 
static int solution1;
static int solution2;
static int solution3;
static int solution4;



int set_seed (const char seed_str[])
{
      int seed;					/* holds the seed */
      int check;				/* check holds the number of items that sscanf checks */		
      char post[2];				/* holds the remainder of seed_str[] after the first integer */

      check = sscanf (seed_str, "%d%1s", &seed, post);		/* read in the seed integer from seed_str[] */

      if(check == 1){						/* conditional statement to check if input is a valid seed, must only be one input */
        srand(seed);						/* if input is valid then set the srand() to the proper seed value */
        return 1;
      }
      else{
        printf("set_seed: invalid seed\n");		/* prinnt error message in the case that the input is not valid */
        return 0;
      }


}


void start_game (int* one, int* two, int* three, int* four)
{
    guess_number = 0;						/* set guess number to 0 */

    solution1 = *one    = rand()%7 + 1;		/* set all soltions by generating a random number */
    solution2 = *two    = rand()%7 + 1;		/* we want all the solutions to be in the range of 1-7 */
    solution3 = *three  = rand()%7 + 1;		/* we do this by modding the randomly generated number by 7 and adding 1 */
    solution4 = *four   = rand()%7 + 1;

}


int make_guess (const char guess_str[], int* one, int* two, int* three, int* four){

    int w, x, y, z;												/* values to store in the guesses from sscanf */
    char post[2];												/* holds value of whatever is left after the first 4 ints in guess_str[] */
    int perfect = 0;												/* integers to hold the values of the types of matches */
    int misplaced = 0;
    int perfect_matches[4] = {0, 0, 0, 0};							/* array that indicates if a solution has been guessed correctly */	
    
    int sols[4] = {solution1, solution2, solution3, solution4};		/* array of solutions to be used later in the method */

    int check = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post); /* read in the guesses and store into the pointers */
    *one = w;
    *two = x;
    *three = y;
    *four = z;

    int guesses[4] = {w, x, y, z};				/* similar to sols[], an array of the user's guesses to be used later in the method */



    


    if(   check == 4
          && (*one >= 1)    && (*one <= 7)
          && (*two >= 1)    && (*two <= 7)
          && (*three >= 1)  && (*three <= 7)
          && (*four >= 1)   && (*four <= 7)     ){

          guess_number++;
    }											/* if else block to test if the if the guesses are valdi */
    else{
        printf("make_guess: invalid guess\n");
        return 0;
    }

    if(*one == solution1){						/* if else block to check for all perfect matches */
        perfect++;
        perfect_matches[0] = 1;					/* if a guess is perfect, we tag the guess as matched */

    }
    if(*two == solution2){
        perfect++;
        perfect_matches[1] = 1;

    }
    if(*three == solution3){
        perfect++;
        perfect_matches[2] = 1;

    }
    if(*four == solution4){
        perfect++;
        perfect_matches[3] = 1;
        
    }

    int i;
    for(i = 0; i<4; i++){					/* two nested for loops to handle the misplaced matches */
    										/* outer loop is meant to go through perfect_guesses[] */
    

      if(perfect_matches[i] != 1){			/* we first check to see if the guess has been 'matched' or perfectly guessed, in which 
      											case we wouldnt want to check it for misplaced matches */

        int j;
        for(j = 0; j<4; j++){				/* once we know that a guess has not been matched, we run through the list of unmatched solutions
        										to see if the guess is a misplaced match with one of the solutions */
            if(guesses[i] == sols[j]){	
     	    if (perfect_matches[j] != 1){		/* the guess and soliution must be equal, and the solution must be unmatched to count as a misplaced match */
              misplaced++;
   
              break;							/* break here to avoid aquiring multiple misplaced matches in the case that the guess in question 
              										is equal to multiple unmatched solutions */
          }
}

           
        }
      }



    }

    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);  /* striaghtforward print statement to display guess number and matches */

    return 1;
}
