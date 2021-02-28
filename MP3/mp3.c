/* Tony Xu (tonyx2) */

/*
In this MP, we used a mathematical algorithm to print a line from pascals triangle 
that was dependent on the user's input of a row. We used two for loops, with the outer
one for printing the row of values and the inner one for doing the calculations of
each value. To fix overflow, instead of using the factorial method of representing 
pascals triangle, we used a product series that would keep the result to be a reasonably sized
value.

Partners: Ishaan Attri (iattri2)
		  Ryan Yoseph (ryosep2)
*/


#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  unsigned long k; /* kth number in row */
  unsigned long i; /* Iteration in product series */

  printf("Enter a row index: ");
  scanf("%d",&row);





  for (k = 0; k <= row; k++){  /* Outer for loop responsible for printing the row */

  	unsigned long a = 1;  /* Initializes output variable */

  	for (i = 1; i <= k; i++){   /* Inner for loop responsible for calculating each number inside the row */

  		a = a * (row + 1 - i)/i; /* Math to calculate the correct output */

  	}
  	
  	printf("%lu ",a); /* print each value in row */
  }


  return 0;
  

}



