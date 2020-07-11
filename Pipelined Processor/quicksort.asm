.quicksort:
	cmp r2,r1
	bgt .recurse
	ret
.recurse:
	sub sp,sp,16
	st ra, [sp]
	st r1, 4[sp]
	st r2, 8[sp]
	
	call .partition
	st r3, 12[sp]
	
	ld r1, 4[sp]
	sub r2, r3, 1
	call .quicksort
	
	ld r3, 12[sp]
	add r1, r3, 1
	ld r2, 8[sp]
	call .quicksort
	
	ld ra, [sp]
	ld r1, 4[sp]
	ld r2, 8[sp]
	add sp, sp, 16
	ret
	
	
	
.partition:
	sub sp,sp,12
	st ra, 8[sp]
	st r1, [sp]
	st r2, 4[sp]

	mul r2, r2, 4    @ r2 -> high
	mul r1,r1,4      @ r1 -> low
	ld r4, [r2]      @ r4 -> pivot = a[high]
	sub r6, r1, 4       @ r6 -> i = low -1 
	mov r8, r1       @ r8 -> j = low
	.loop: 
		cmp r2,r8     @ if j < high
		bgt .compare  @ go to compare
		beq .break    @ else go to break
	.compare:
		ld r5, [r8]   @ r5 -> a[j] 
		cmp r4,r5	  @  pivot > a[j]
		bgt .swap
		add r8, r8, 4
		b .loop
	.swap:
		add r6, r6,4  @ i++
		ld r7, [r6]   @ r7 -> a[i]	
		st r7, [r8]
		st r5, [r6]
		add r8, r8, 4
		b .loop
	.break:           @ r8 == r2 -> j == high
		ld r7, 4[r6]  @ r7 -> a[i+1]
		st r7, [r2]
		st r4, 4[r6]
		add r3, r6,4
		div r3, r3, 4
		ld ra, 8[sp]
		ld r1, [sp]
		ld r2, 4[sp]
		add sp,sp,12
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

	mov r1, 0          @ Starting address of the array
	
	@ Retreive the end address of the array
	mov r2, 5	@ REPLACE 5 WITH N-1, where, N is the number of numbers being sorted
	
	
 	@ ADD YOUR CODE HERE 

	call .quicksort

 	@ ADD YOUR CODE HERE

	@ Print statements for the result
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

