/*
Ryan Yoseph (ryosep2)

In this MP, we wrote two functions, one to test if a number was prime or not
and another to print out the semiprimes. To test if it was a prime number
or not, we set up a loop to see if the number was divisible by anything
other than 1 and itself. Specifically, the modulus was used to indicate whether
or not a number was prime. To print out the semiprimes between a range, we set up 
two for loops, one loop to go from number to number in the range, and the inner 
for loop to test whether or not the number was a semiprime or not. If it was a semiprime,
the number had to be non-prime and be divisible by a prime. After dividing by a prime,
the quotient also had to be prime for it to be semiprime. After all that, the number
would be printed and the outer for loop would move on to test the next number in the range.

Partners:
Tony Xu (tonyx2)
Ishaan Attri (iattri2)


*/
#include <stdlib.h>
#include <stdio.h>


int is_prime(int number); 							/* Function declaration */
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);

   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   /* TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b) */

   return print_semiprimes(a,b); 				  /* Calling the print semiprimes function */
   
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
	int i; 										 /* Declaring variable to be set as a divisor */
	for (i = 2; i < number; i++){ 				 /* For loop to increment the divisor to test if number can be divided by  */
		if(i != number && number % i == 0){ 	 /* anything other than 1 and itself */
			return 0; 					         /* If number is not prime, return 0 */
		}
	}
	return 1;									 /* If number is prime, return 1 */
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
	int n;  									 /* Variable declaration for outer for loop */
	int y;										 /* Variable declaration for inner for loop */
	int z; 										 /* Variable declaration for storing the quotient after dividing possible semiprime by divisor */
	int u; 										 /* Variable declaration for storing outcome of testing if value is a prime or not */
	int w;										 /* Variable declaration for holding the value of the return value */

	for (n = a; n <= b; n++){ 					 /* For loop for moving from one number to next in the given range between a and b */
		if (is_prime(n) == 0){ 					 /* If number is prime, then it can't be a semiprime */
		for (y = 2; y < n; y++){ 				 /* For loop for the divisor for testing if semiprime */
			if (n % y == 0 && is_prime(y) == 1){ /* If the number is divisible by divisor, and if the divisor is also a prime, then move on to */
				z = n/y;                         /* next step in seeing if quotient is also prime */
				u = is_prime(z); 				 /* Testing if value is prime or not */
				if (u == 1){                     /* If quotient is also prime, then the value tested is a semiprime */
					printf("%d ", n); 			 /* Print the semiprime value*/
					w = 1;  					 /* Set variable to hold return value of 1 */
					break; 						 /* If number is semiprime, then move on to next number and go back to outer for loop */


			}
			
				}
				
			
		}
				
}


}
if (w == 1)  									 /* Set return values */
	return 1;
else
	return 0;
}
