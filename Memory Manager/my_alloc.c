/*
	Author : 	Vivek Muskan (2017MT10755)
	Description : 	This code request a blank memory and create its own memory management system including malloc() & free().
	Function : 	my_init(), my_alloc(), my_free(), my_heapinfo(), my_clean() & memory_visualizer()**(Extra function for memory visualization
	Contact/Help :	mt1170755@iitd.ac.in
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

#define psize 4096 // page size = 4KB

char *home;			   // pointer of page allocated
int *no_of_max_block;  // maximum no. of 8-byte block possible
int *no_of_free_block; // no. of free 8-byte block
int *SIZE;			   // pointer to size array for allocated blocks
char *DATA;			   // pointer to 8-byte block array

// 1. my_init() --> Request Memory and create managing structure
int my_init()
{
	// Requesting page
	home = mmap(NULL, psize, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	// Error message on allocation failure
	if (home == MAP_FAILED)
	{
		printf("ERROR : mmap() : Memory mapping failed\n");
		exit(1);
	}

	// Calculating max no. of possible 8-byte block with defined psize
	int it = sizeof(int);
	int n = (psize - 2 * it) / (it + 8);	// To understand this, please refer to comment file (My Memory structure) or mail me
	//printf("sizeof(char*) = %d, psize = %d, n = %d\n",p,psize,n);

	// Pointing main variables in my memory page
	no_of_max_block = (int *)(home);
	no_of_free_block = (int *)(home + 4);
	SIZE = (int *)(home + 8);
	DATA = (char *)(SIZE + n);

	// Saving intial values of main variables
	*no_of_max_block = n;
	*no_of_free_block = n;
	//memset(SIZE, -1, n);	// -1 : Unallocated block
	for (int i = 0; i < n; i++)
	{
		SIZE[i] = -1;
	}

	/*// DEBUGGER
	printf("my_init() : successful\n");
	printf("home/N     = %p	*N = %d\n",home, *home);
	printf("home+1/C   = %p	*C = %d\n",home+1, home[1]);
	printf("home+2/S   = %p	*S = %d\n",SIZE, *SIZE);
	printf("home+2+N/D = %p	*D = %d\n",DATA, *DATA);
	*/

	return 0;
}

// 2. my_alloc() --> Allocates memory of given size
void *my_alloc(int s)
{
	if (s % 8 != 0 || s<=0)
		return NULL; // Not multiple of 8-bytes

	// First-Fit algorithm
	int n = -1; // nth block is free

	// Checking first unallocated block
	for (int i = 0; i < *no_of_max_block; i++)
	{
		if (SIZE[i] == -1)
		{ // found unallocated block
			int free_to_use = 1;
			// checking if size meets the demand
			for (int j = 0; j < (s / 8); j++)
			{
				if (SIZE[i + j] != -1)
				{
					free_to_use = 0;
					break;
				}
			}
			if (free_to_use)
			{
				n = i;
				break;
			}
		}
		if (n != -1)
			break;
	}
	if (n == -1){ // Couldn't find any free chunk for given size
//->		printf("WARNING : my_alloc() : Couldn't find any chunk of %d-Byte\n", s);
		return NULL;
	}

	// Saving size and updating heap info
	SIZE[n] = (s / 8);
	for (int j = 1; j < (s / 8); j++)
		SIZE[n + j] = 0; // 0 : Occupied
	*no_of_free_block -= (s / 8);

	return (void *)(DATA + 8 * n);
}

// 3. my_free() --> free up the given block for further use
void my_free(void *pt)
{
	if(pt == NULL) {printf("WARNING : my_free() : null pointer : Invalid pointer\n");return;}
	char *ptr = (char *)pt;
	int diff = (int)(ptr - DATA);
	if (diff < 0 || diff >= *(no_of_max_block)*8 || diff % 8 != 0)	// Error Handling
	{
		printf("WARNING : my_free() : %p Invalid pointer\n", ptr);
		return;
	}
	int block_no = ((int)(ptr - DATA)) / 8;
	int n = SIZE[block_no];
	if (n == 0 || n == -1)	// If unallocated or middle of used memory block is pointed
	{
		printf("WARNING : my_free() : %p Invalid pointer\n", ptr);
		return;
	}
	for (int j = 0; j < n; j++)
		SIZE[block_no + j] = -1; // Setting block status as free
	*no_of_free_block += n;		 // Updating heap info
}

// 4. my_clean() --> unmaps the memory allocated by my_init()
void my_clean()
{
	int err = munmap(home, psize);
	if (err != 0)
	{
		printf("ERROR : UnMapping Failed\n");
		exit(1);
	}
}

// 5. my_heapinfo() --> Gives basic information about heap
void my_heapinfo()
{
	int a, b, c, d, e, f;

	int header = (*no_of_max_block) * sizeof(int);
	int data = (*no_of_max_block) * 8;
	int metadata = psize - header - data;
	int occupied = ((*no_of_max_block) - (*no_of_free_block)) * 8;

	a = data + header;
	b = occupied + header;
	c = data - occupied;
	d = (*no_of_max_block) - (*no_of_free_block);
	int min = (*no_of_max_block) + 1;
	int max = -1;

	// Checking first unallocated block
	for (int i = 0; i < *no_of_max_block; i++)
	{
		if (SIZE[i] == -1)
		{ // found unallocated block
			int cnt = 0;
			while (i < *no_of_max_block && SIZE[i] == -1)
			{
				i++;
				cnt++;
			}
			if (cnt > max)
				max = cnt;
			if (cnt < min)
				min = cnt;
			i--;
		}
	}
	if (min == (*no_of_max_block) + 1)
	{
		min = 0;
		max = 0;
	}

	e = 8 * min;
	f = 8 * max;

	// Do not edit below output format
	printf("=== Heap Info ================\n");
	printf("Max Size: %d\n", a);
	printf("Current Size: %d\n", b);
	printf("Free Memory: %d\n", c);
	printf("Blocks allocated: %d\n", d);
	printf("Smallest available chunk: %d\n", e);
	printf("Largest available chunk: %d\n", f);
	printf("==============================\n");
	// Do not edit above output format
	return;
}

// 6. memory_visualizer() --> show memory address and content at any given time in 'int' format
// CAUTION : Use for low page size for better visual experience.
void memory_visualizer()
{
	printf("\n======================================================= MY MEMORY ============================================================================\n");
	my_heapinfo();
	printf("SIZE status --> {-1: Unallocated	0: Occupied	x(>0): Next x block Occupied (including current) }\n");
	printf("____________________________________________________________________________________________________________________________________________\n");
	printf("SIZE (4-Byte, 'int')	|	MEMORY ADDRESS (8-Byte)		BLOCK NO. 		Each Byte printed as 'int'\n");
	printf("____________________________________________________________________________________________________________________________________________\n");
	printf("%p-> %d(max)|	%p -> %d (free)		Offset	[0]	[1]	[2]	[3]	[4]	[5]	[6]	[7]\n", no_of_max_block, *no_of_max_block, no_of_free_block, *no_of_free_block);
	printf("____________________________________________________________________________________________________________________________________________\n");

	for (int i = 0; i < *no_of_max_block; i++)
	{
		int k = 8 * i;

		printf("%p  -> %d	|	[%p - %p] (%d)	->	%d	%d	%d	%d	%d	%d	%d	%d\n",
			   SIZE + i, SIZE[i], DATA + k, DATA + k + 7, (i + 1), DATA[k], DATA[k + 1], DATA[k + 2], DATA[k + 3], DATA[k + 4], DATA[k + 5], DATA[k + 6], DATA[k + 7]);
	}
	printf("\n=============================================================================================================================================\n");
}
