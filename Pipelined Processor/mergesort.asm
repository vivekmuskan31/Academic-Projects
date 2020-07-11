.merge:
	sub r4, r3, r1
	add r4, r4, 2   
	mul r4, r4, 4    @ r4 -> Size of temporary array
	
	sub sp, sp, r4
	sub sp, sp, 20
	st ra, [sp]
	st r1, 4[sp]     @ r1 -> l
	st r2, 8[sp]     @ r2 -> m
	st r3, 12[sp]    @ r3 -> r
	
	sub r5, r2, r1
	add r5, r5, 1    @ r5 -> n1
	sub r6, r3, r2   @ r6 -> n2
	
	@ Creating temp array
	add r7, sp, 16   @ L[n1] -> r7
	mul r8, r5, 4
	add r8, r8, r7
	add r8, r8, 4    @ R[n2] -> r8 
	
	@copy data to temp array
	mov r9, 0        @ r9 -> i
	.loop1:
		cmp r5, r9
		bgt .copy1
		b .break1
	.copy1:
		add r10, r1, r9 @ temp = l + i
		mul r10, r10, 4
		ld r10, [r10]
		mul r11, r9, 4
		add r11, r11, r7  
		st r10, [r11]   @ L[i] = arr[l+i]
		add r9, r9, 1
		b .loop1
	.break1:
		mov r9, 0       @ r9 -> j
		b .loop2
	
	.loop2:
		cmp r6, r9
		bgt .copy2
		b .break2
	.copy2:
		add r10, r2, r9
		add r10, r10, 1  @ temp = m + j + 1
		mul r10, r10, 4
		ld r10, [r10]
		mul r11, r9, 4
		add r11, r11, r8
		st r10, [r11]    @ R[j] = arr[m+1+j]
		add r9, r9, 1
		b .loop2
	.break2:
		@ merging the sub arrays
		mov r9, 0		@ r9 -> i
		mov r10, 0 		@ r10 -> j
		mov r11, r1		@ r11 -> k = l
		b .loop3
		
	.loop3:
		cmp r5, r9
		bgt .loop4
		b .break3
	.loop4:
		cmp r6, r10
		bgt .continue
		b .break4
	.continue:
		mul r12, r9, 4
		add r12, r12, r7
		ld r12, [r12]    @ r12 -> L[i]
		mul r13, r10, 4
		add r13, r13, r8
		ld r13, [r13]    @ r13 -> R[j]
		cmp r13, r12
		bgt .left
		beq .left
		b .right
	.left:
		mul r13, r11, 4
		st r12, [r13]    @ arr[k] = L[i]
		add r9, r9, 1
		add r11, r11, 1
		b .loop3
	.right:
		mul r12, r11, 4
		st r13, [r12]    @ arr[k] = R[j]
		add r10, r10, 1
		add r11, r11, 1
		b .loop3
	.break3:
		b .break4
	.break4:             @ Clear r12 and r13
		mov r12, 0
		mov r13, 0
		b .loop5
		
	
	
	@ Copy the remaining elements of L[i] if there
	.loop5:
		cmp r5, r9
		bgt .left1
		b .break5
	.left1:
		mul r13, r11, 4
		mul r12, r9, 4
		add r12, r12, r7
		ld r12, [r12]    @ Extract L[i]
		st r12, [r13]    @ arr[k] = L[i]
		add r9, r9, 1
		add r11, r11, 1
		b .loop5
	.break5:
		b .loop6
	
	@ Copy the remaining elements of R[j] if there	
	.loop6:
		cmp r6, r10
		bgt .right1
		b .break6
	.right1:
		mul r13, r11, 4
		mul r12, r10, 4
		add r12, r12, r8
		ld r12, [r12]    @ Extract R[j]
		st r12, [r13]    @ arr[k] = R[j]
		add r10, r10, 1
		add r11, r11, 1
		b .loop6
	.break6:
		ld ra, [sp]
		ld r1, 4[sp]     @ r1 -> l
		ld r2, 8[sp]     @ r2 -> m
		ld r3, 12[sp]    @ r3 -> r
		add sp, sp, 20
		add sp, sp, r4
		ret

.mergesort:
	cmp r3, r1
	bgt .compare
	ret
.compare:
	sub sp, sp, 16
	st ra, [sp]
	st r1, 4[sp]
	st r3, 12[sp]
	
	sub r2, r3,r1
	div r2, r2, 2
	add r2, r2, r1
	st r2, 8[sp]
	
	@ Calling MergeSort Left
	mov r3, r2
	call .mergesort
	
	@ Calling MergeSort Right
	ld r1, 8[sp]
	add  r1, r1, 1
	ld r3, 12[sp]
	call .mergesort
	
	@ Merging Sorted Left and Right Part
	ld r1, 4[sp]
	ld r2, 8[sp]
	ld r3, 12[sp]
	call .merge
	
	ld ra, [sp]
	add sp, sp, 16
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

	mov r2, 0          @ Starting address of the array
	
	@ Retreive the end address of the array
	mov r3, 5	@ REPLACE 5 WITH N-1, where, N is the number of numbers being sorted
	mov r1, 0
	
	@ ADD YOUR CODE HERE 
	
	call .mergesort

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

