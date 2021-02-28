; mp2.asm
; Implement a stack calculator that can do the following operations:
; ADD, SUBTRACT, MULTIPLY, DIVIDE

; Inputs:
;   Console - postfix expression
; Outputs:
;   Console - [0 - F]{4}, evaluation of postfix expression
;   Register R5 - [0 - F]{4}, evaluation of postfix expression

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; In this mp, we implemented a stack calculator that would read values and do arithmetic in reverse polish notation. We used a similar PRINT_HEX algorithm as the one in mp1.
; When the user inputted the first character, our EVALUATE branch would use process of elimination to figure out if the input was invalid, a space, an equal sign, an operator,
; or a number. Once we knew what type of input the character was, if the input was a number, we would push that number onto the stack, update the stack pointer, and then
; branch back to EVALUATE to read the next input. If the input was a space, we would not push it on the stack. If the input was an equal sign, we would pop the last value from
; the stack, and then check if the stack was clear. If it was, our code would continue to the PRINT_HEX and we would output the result. Finally, if the output was an operator,
; we would branch to the specific loop that would perform the arithmetic, pop two values from the stack, load them in seperate registers, and then compute the results. During
; the course of our code, if the input is not meant for calculations, then we would print out INVALID EXPRESSION. When the stack is empty and our value has been printed to the
; screen, we HALT the program and end the code. 
;
;
;
;	partners: tonyx2, iattri2

.ORIG x3000

MAIN
					JSR EVALUATE				; Jump to EVALUATE

DONE 				HALT						; Program is Done 


; PRINT_HEX
;   Description: prints out the value in R3 to the console
;   Inputs: R5 - value in register to be printed out
;   Outputs: Value printed to the console

PRINT_HEX			AND R1, R1, #0
					ADD R1, R1, R5				; Store value to be printed in R1
					AND R2, R2, #0				; Clear R2
    				AND R0, R0, #0    			; Clear R0
    				AND R3, R3, #0    			; Holds the digit counter
    				AND R4, R4, #0    			; Holds the bit counter
    				ADD R3, R3, #-4				; Initialize digit counter

DIGIT				AND R4, R4, #0				; Clear Value in bit counter
    				ADD R4, R4, #-4				; Initialize bit counter
    				AND R0, R0, #0				; Clear past value in R0 to output new 4

BIT					ADD R0, R0, R0
    				ADD R5, R5, #0
    				BRzp x0001					; If R5 has 1 in significant bit, then add 1 to R0. If R5 has 0 in significant bit, then skip.
    				ADD R0, R0, #1
  				  	ADD R5, R5, R5				; Left shift R5
  				  	ADD R4, R4, #1				; Increment bit counter
  				  	BRn BIT         			; Four iterations counting bits
  				  	ADD R0, R0, #15
  				  	ADD R0, R0, #15
  				  	ADD R0, R0, #15
  				  	ADD R0, R0, #3    			; Ascii table conversion to make hexadecimal into hex
					AND R6, R6, #0				; Clear R6 to make sure it starts at 0.
					ADD R6, R0, #0				; Store the data in R0 into R6 so we do not tamper with the data in R0.
					ADD R6, R6, #-16
					ADD R6, R6, #-16
					ADD R6, R6, #-16			; This step allows us to check if the data stored in R0 is a letter or a number by taking the difference.
					ADD R6, R6, #-9
					BRnz #1
					ADD R0, R0, #7				; If the data stored in R0 is a letter, then we need to shift the value by 7 to print the proper letter.
  				  	OUT             			; Print the number into screen
    				ADD R3, R3, #1    			; Increment digit counter
    				BRn DIGIT         			; Loop until we have all four digits printed
    				AND R0, R0, #0
    				ADD R0, R0, x000A
    				OUT     					; Print new line
					ADD R5, R5, R1
					RET                         ; Return back to END_GAME to HALT the program 



; 	EVALUATE
;   Description: handles input from console
;   Inputs: Console - input
;   Outputs: Console - evaluation of expression or error

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 				Table of Registers
; 				R0 - to print/hold result of subroutine/input
; 				R1 - use to save value of R7 when calling subroutine within EVALUATE
; 				R2 - no particular assignment
; 				R3 - second thing popped from stack (in other words, most recent input)
; 				R4 - first thing popped from stack (could contain input from equation or result of prior calculations)
; 				R5 - holds end value
; 				R6 - temporary Register
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


EVALUATE				GETC 					; get input from user
						OUT
						AND R6, R6, #0 			; Clear R6
						ADD R6, R0, R6			; store input to R6
						ADD R6, R6, #-16
						ADD R6, R6, #-16
						BRz EVALUATE 			; this is to check if input is space. If it is, do not push anything to stack
						BRn INVALID 			; if the input is less than a space it is invalid

						ADD R6, R6, #-16
						ADD R6, R6, #-13
						BRz END_GAME			; checks if input is "=" by subtracting a total of x3D (x20 from the space check and 1D from after)
						BRp INVALID 			; if the input is greater than a "=" in ASCII, then it is invalid

						AND R6, R6, #0
						ADD R6, R6, R0			; reset R6 value to R0
						ADD R6, R6, #-16		; start checking if input is a number (above Hex x30 and below Hex x39)
						ADD R6, R6, #-16
						ADD R6, R6, #-16
						BRn CHECK_MUL			; if we know input is less than x30 then skip the check for less than x39
						AND R2, R2, #0			; clear R2 before using it as a temp Register
						ADD R2, R2, #9
						NOT R6, R6
						ADD R6, R6, #1			; negate R6
						ADD R2, R2, R6			; 9 - R6 to find out if input is less than x39
						BRn INVALID				; If it is not a number skip to next check
						ST R7, SAVE_R7A			; save R7
						JSR NUM                 ; Now we know that the input is a number 
						LD R7, SAVE_R7A			; restore value of R7 that takes us back up to MAIN
						BRnzp EVALUATE			; Branch back to EVALUATE to scan for next input 



CHECK_MUL				AND R6, R6, #0			; Clear value stored in R6
						ADD R6, R6, R0			; reset R6 value to R0
						ADD R6, R6, #-16
						ADD R6, R6, #-16
						ADD R6, R6, #-10		; subtract x2A to check if input is *
						BRn INVALID 			; this means input is between x20 (space) and x2A meaning it is invalid input
						BRp CHECK_ADD			; if it isnt * then skip to next check
						ST R7, SAVE_R7A			; save R7
						JSR MUL                 ; We know now that the operator is an * 
						LD R7, SAVE_R7A			; restore value of R7 that takes us back up to MAIN
						BRnzp EVALUATE

CHECK_ADD				ADD R6, R6, #-1			; subtract x2B (x2A from before and -1 from now) to check if input is +
						BRp CHECK_SUB			; if it isnt + then skip lines that call PLUS
						ST R7, SAVE_R7A			; save R7
						JSR PLUS
						LD R7, SAVE_R7A			; restore value of R7 that takes us back up to MAIN
						BRnzp EVALUATE

CHECK_SUB				ADD R6, R6, #-2			; subtract x2D (x2B from before and -2 from now) to check if input is -
						BRn INVALID
						BRp CHECK_DIV			; if it isnt - then skip lines that call MIN
						ST R7, SAVE_R7A			; save R7
						JSR MIN
						LD R7, SAVE_R7A			; restore value of R7 that takes us back up to MAIN
						BRnzp EVALUATE

CHECK_DIV				ADD R6, R6, #-2			; subtract x2F (x2D from before and -2 from now) to check if input is /
						BRn INVALID
						BRp END_CHECK			; if it isnt + then skip lines that call PLUS
						ST R7, SAVE_R7A			; save R7
						JSR DIV
						LD R7, SAVE_R7A			; restore value of R7 that takes us back up to MAIN
						BRnzp EVALUATE

END_CHECK				RET						; at this point the input must be x3A,x3B, or x3C which are invalid



;		END_GAME
;		subroutine to handle the resulting input when 
;
END_GAME				JSR POP
						LD R4, STACK_TOP
						LD R3, STACK_START
						NOT R3, R3
						ADD R3, R3, #1
						ADD R3, R3, R4
						BRnp INVALID  			; branch to INVALID Subroutine due to error of multiple things left in STACK
						AND R5, R5, #0			
						ADD R5, R5, R0			; Load value of output to screen into R5
						JSR PRINT_HEX
						BRnzp DONE              ; HALT the program



;		INVALID
;		method to handle any error that occours
;
INVALID  				LEA R0, INVALID_EX		; Load R0 with the first memory address for INVALID EXPRESSION
						PUTS					; Print String
						BRnzp DONE              ; HALT the program after deemed invalid 


; 	NUM
; 	method to handle when input is  a number
;
NUM 					ADD R0, R0, #-16
						ADD R0, R0, #-16
						ADD R0, R0, #-16		; Subtract x30 to get to the proper hexadecimal value to do the operations 
						ST R7, SAVE_R7B			; save R7
						JSR PUSH
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						RET


; 	PLUS
;   Description: adds two numbers (R0 = R3 + R4)
;   Inputs: R3 - addend  R4 - addend
;   Outputs: R0 - sum

PLUS					AND R4, R4, #0
						AND R3, R3, #0

						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1			; Check if there was underflow
						BRz INVALID
						ADD R4, R4, R0

						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1
						BRz INVALID
						ADD R3, R3, R0

						AND R0, R0, #0			
						ADD R0, R3, R4.         ; Do the addition 

						ST R7, SAVE_R7B			; save R7
						JSR PUSH
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN

						RET

; MIN
;   Description: subtracts two numbers (R0 = R3 - R4)
;   Inputs: R3 - minuend
;	    R4 - subtrahend
;   Outputs: R0 - difference

MIN						AND R4, R4, #0
						AND R3, R3, #0

						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1
						BRz INVALID
						ADD R4, R4, R0

						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1
						BRz INVALID				; checking for underflow
						ADD R3, R3, R0

						AND R0, R0, #0
						NOT R4, R4
						ADD R4, R4, #1 ; make R4 = -R4
						ADD R0, R3, R4 ; calculate difference of R3 and R4

						ST R7, SAVE_R7B			; save R7
						JSR PUSH
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN


						RET



; MUL
;   Description: multiplies two numbers (R0 = R3 * R4)
;   Inputs: R3 - factor
;	    R4 - factor
;   Outputs: R0 - product

MUL						AND R4, R4, #0
						AND R3, R3, #0

						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1
						BRz INVALID
						ADD R4, R4, R0
						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1
						BRz INVALID
						ADD R3, R3, R0

						ADD R4, R4, #-1 ;
MUL_2					ADD R4, R4, #0
						BRz MUL_3
						ADD R0, R0, R3
						ADD R4, R4, #-1
						BRnz MUL_3
						BRp MUL_2


MUL_3					ST R7, SAVE_R7B			; save R7
						JSR PUSH
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						RET

; DIV
;   Description: divides two numbers (R0 = R3 / R4)
;   Inputs: R3 - numerator
;	  R4 - denominator
;   Outputs: R0 - quotient
DIV						AND R4, R4, #0
						AND R3, R3, #0

						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1
						BRz INVALID
						ADD R4, R4, R0

						ST R7, SAVE_R7B			; save R7
						JSR POP
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						ADD R5, R5, #-1
						BRz INVALID
						ADD R3, R3, R0


						AND R0, R0, #0
						NOT R4, R4
						ADD R4, R4, #1
						AND R6, R6, #0
						ADD R6, R3, #0

DIV_2					ADD R6, R6, R4
						BRn #2
						ADD R0, R0, #1
						BRp DIV_2

						ST R7, SAVE_R7B			; save R7
						JSR PUSH
						LD R7, SAVE_R7B			; restore value of R7 that takes us back up to MAIN
						RET



; PUSH
;   Description: Pushes a charcter unto the stack
;   Inputs: R0 - character to push unto the stack
;   Outputs: R5 - 0 (success) or 1 (failure/overflow)
;   Registers: R3 - stores STACK_END
;	  R4 - stores STACK_TOP

PUSH					ST R3, PUSH_SaveR3		; save R3
						ST R4, PUSH_SaveR4		; save R4
						AND R5, R5, #0
						LD R3, STACK_END
						LD R4, STACK_TOP
						ADD R3, R3, #-1
						NOT R3, R3
						ADD R3, R3, #1
						ADD R3, R3, R4
						BRz OVERFLOW			;stack is full
						STR R0, R4, #0			;no overflow, store value in the stack
						ADD R4, R4, #-1			;move top of the stack
						ST R4, STACK_TOP		;store top of stack pointer
						BRnzp DONE_PUSH
						OVERFLOW
						ADD R5, R5, #1
						DONE_PUSH
						LD R3, PUSH_SaveR3
						LD R4, PUSH_SaveR4
						RET

						PUSH_SaveR3	.BLKW #1
						PUSH_SaveR4	.BLKW #1


; POP
;   Description: Pops a character off the stack
;   Inputs:
;   Outputs: R0 - character popped off the stack
;	     R5 - 0 (success) or 1 (failure/underflow)
;   Registers: R3 - stores STACK_END
;	       R4 - stores STACK_TOP

POP 					ST R3, POP_SaveR3		; save R3
						ST R4, POP_SaveR4		; save R4
						AND R5, R5, #0			; clear R5
						LD R3, STACK_START
						LD R4, STACK_TOP
						NOT R3, R3
						ADD R3, R3, #1
						ADD R3, R3, R4
						BRz UNDERFLOW
						ADD R4, R4, #1
						LDR R0, R4, #0
						ST R4, STACK_TOP
						BRnzp DONE_POP
						UNDERFLOW
						ADD R5, R5, #1
						DONE_POP
						LD R3, POP_SaveR3
						LD R4, POP_SaveR4
						RET


POP_SaveR3				.BLKW #1
POP_SaveR4				.BLKW #1
STACK_END				.FILL x3FF0
STACK_START				.FILL x4000
STACK_TOP				.FILL x4000
SAVE_R7A 				.BLKW #1
SAVE_R7B 				.BLKW #1
INVALID_EX				.STRINGZ "INVALID EXPRESSION"

.END
