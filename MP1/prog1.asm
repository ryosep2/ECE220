;
; The code given to you here implements the histogram calculation that
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of
; code to print the histogram to the monitor.
;
; If you finish your program,
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string
; terminated by a NUL character.  Lower case and upper case should
; be counted together, and a count also kept of all non-alphabetic
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance)
; should be stored starting at x3F00, with the non-alphabetic count
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram

	; fill the histogram with zeroes
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to star


; For this MP, we printed out the histogram provided to us in the code. We did this by implementing a loop which cycled through each line 
; of the histogram and then individually converting four bits at a time into its proper hexadecimal 
; notation and printing it to the monitor. For example, if the
; character "A" had 7 occurences in the the histogram, the LC3 would first print "0", then "0", then "0", then finally a "7". 
; After 4 bits have been copied and evaluated, we would then increment our digit counter by 1, then cycle through the bit loop until all 
; 4 digits were printed to the screen.After this was done, we created a new line, incremented our bin counter, and then 
; checked if our program was complete with all 27 bins printed out.
; 
;
; partners: tonyx2, iattri2
;
;
;			*****New regsiter table*****
;			R0 stores data to be printed
;			R1 acts as a counter that goes through 27 iterations for each bin (Each bin stores the # of characters @ and A-Z)
;			R2 Holds current memory address of bin
;			R3 Holds digit counter for printing hex
;			R4 Holds bit counter or printing hex
;			R5 Holds data at address in R2
;			R6 acts as a temporary register



PRINT_HIST		AND R2, R2, #0		;clear value remaining in R2
				ADD R2, R2, R0		;R0 still holds value of x3F00 at this point
				AND R0, R0, #0		;clear data  in R0
				AND R1, R1, #0		;Initialize R1 to 0

BIN				AND R0, R0, #0		
				ADD R0, R0, R1		;During this step, we use R1 as a relative pointer to find the correct memory address of whichever character we need to print 
				ADD R0, R0, #15		;We add 64 to R0 so that we can print out the corresponding ASCII character 
				ADD R0, R0, #15		;Once we have noted all occurences of the character in the histogram, we loop back to BIN.
				ADD R0, R0, #15		
				ADD R0, R0, #15		
				ADD R0, R0, #4		
				OUT					;Print relevant letter (Order is as follows: @, A, B, C, D, etc.)
				AND R0, R0, #0		;Clear R0 
				ADD R0, R0, #15		
				ADD R0, R0, #15
				ADD R0, R0, #2
				OUT					;print new space
				LDR R5, R2, #0		;store data at R2 into R5

				AND R3, R3, #0		; Clear any value left in R3
				ADD R3, R3, #-4		; Initialize digit counter

DIGIT	 		AND R4, R4, #0		;
				ADD R4, R4, #-4		;Initialize bit counter
				AND R0, R0, #0
BIT				ADD R0, R0, R0		;Left shift R0 
				ADD R5, R5, #0		;This step is merely to check if the data in R5 is negative or positive
				BRzp x0001			;If the first digit is a 0, then branch to line 138. If else, then add a 1 to R0, our data to be printed.
				ADD R0, R0, #1
				ADD R5, R5, R5		;Left shift to get the next bit
				ADD R4, R4, #1		;Add 1 to our bit counter until four iterations are complete
				BRn BIT				;Branch until four bits have been copied 
				ADD R0, R0, #15		
				ADD R0, R0, #15		;
				ADD R0, R0, #15		;In this step, we add 48 to the data stored in R0. Since decimal 48 is 0 in ASCII, this allows us to print the corresponding
				ADD R0, R0, #3		;numbers onto the screen by jumping to the right position.
				AND R6, R6, #0		;Clear R6 to make sure it starts at 0.
				ADD R6, R0, #0		;Store the data in R0 into R6 so we do not tamper with the data in R0.
				ADD R6, R6, #-16
				ADD R6, R6, #-16	;
				ADD R6, R6, #-16	;This step allows us to check if the data stored in R0 is a letter or a number by taking the difference.
				ADD R6, R6, #-9		
				BRnz #1
				ADD R0, R0, #7		;If the data stored in R0 is a letter, then we need to shift the value by 7 to print the proper letter.
				OUT					;print digit to monitor
				ADD R3, R3, #1		; Increment digit counter
				BRn DIGIT			; Loop back to DIGIT until we have successfully printed 4 digits onto the monitor for that character.
				AND R0, R0, #0		
				ADD R0,  R0, x000A
				OUT 				;print new line
				ADD R2, R2, #1		;Increment pointer so that we can find the proper address of the next character
				ADD R1, R1, #1		;Increment bin counter after successfully completing one bin
				AND R6, R6, #0		; Clear temporary register for future usage
				ADD R6, R1, #0		
				ADD R6, R6, #-16	;Once we have gone through all characters, that would be 27 iterations (0-26). 
				ADD R6, R6, #-10	; If we add -26 to R6 and get zero, we know that we have completed all characters and can therefore halt the program.
				BRnz  BIN


DONE		HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
