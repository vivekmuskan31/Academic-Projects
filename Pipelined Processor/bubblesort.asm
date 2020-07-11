.bubblesort:
	cmp r1, 1
	beq .return
	bgt .continue
	b .return
.return:
	mov r0, 0
	ret
.continue:
	ld r2, [r0]
	ld r4, 4[r0]
	cmp r2,r4
	bgt .swap
	st r2, [r0]
	st r4, 4[r0]
	add r0, r0, 4
	sub r1, r1, 1
	b .bubblesort
.swap:
	st r4, [r0]
	st r2, 4[r0]
	add r0, r0, 4
	sub r1, r1, 1
	b .bubblesort
	ret	



.main:

	@ Loading the values as an array into the registers
	mov r0, 0    
	mov r1, 12	@ replace 12 with the number to be sorted
	st r1, 0[r0]
	mov r1, 7	@ replace 7 with the number to be sorted
	st r1, 4[r0]
	mov r1, 11  @ replace 11 with the number to be sorted
	st r1, 8[r0]
	mov r1, 9   @ replace 9 with the number to be sorted
	st r1, 12[r0]
	mov r1, 3   @ replace 3 with the number to be sorted
	st r1, 16[r0]
	mov r1, 15  @ replace 15 with the number to be sorted
	st r1, 20[r0]
	@ EXTEND ON SIMILAR LINES FOR MORE NUMBERS

	mov r2, 0       @ Starting address of the array
	
	@ Retreive the end address of the array
	mov r3, 6	@ REPLACE 6 WITH N, where, N is the number of numbers being sorted
	
	@ ADD YOUR CODE HERE

	.loop:
		mov r1, r3
		call .bubblesort
		sub r3,r3,1
		cmp r3,1
		bgt .loop
	
	@ ADD YOUR CODE HERE

	@ Print statements
	ld r1, 0[r0]
	.print r1
	ld r1, 4[r0]
	.print r1
	ld r1, 8[r0]
	.print r1
	ld r1, 12[r0]
	.print r1
	ld r1, 16[r0]
	.print r1
	ld r1, 20[r0]
	.print r1
	@ EXTEND ON SIMILAR LINES FOR MORE NUMBERS

