/*
	Author : 		Vivek Muskan (2017MT10755)
	Description : 	Pagetable is simulated based on 5 different page replacement policies
	Policies	:	Optimal, LRU, Clock, FIFO and Random	
	Contact/Help : 	mt1170755@iitd.ac.in
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max_no_of_frame 1000	// Max size of physical memory
#define seed 5635

void swap(int i, int cnt, int* lru){	// Simple swapping function
	int p;								// for LRU implementation
	for(int j=0;j<cnt;j++){
		if(lru[j]==i) {p =j; break;}
	}
	int temp = lru[p];
	for(int x=p;x<cnt-1;x++) lru[x] = lru[x+1];
	lru[cnt-1] = temp;
}

// FIFO, LRU, CLOCK and RANDOM all are implemented inside this function
void practical_policies(int* res, char fname[], int fno, bool ver, char stgy[]){
	
	srand(seed);		// For random
	int fifo_counter=0;	// fifo starting point
	int clock_hand=0;	// intial cloack hand

	// Reading file
	FILE *f;
	f = fopen(fname,"r");
	if(f==NULL){ printf("Error! opening file\n"); exit(1);}
	

	// Pagetable entries
	int phy_mem[fno];	// PFN
	bool dirty[fno];	// dirty bit -> for write/drop
	bool access[fno];	// access bit -> for clock algo
	int* lru = malloc(fno*sizeof(int));	// for lru implementation
	memset(phy_mem, 0, fno*sizeof(phy_mem[0]));
	memset(dirty, false, fno*sizeof(dirty[0]));
	memset(access, 0, fno*sizeof(access[0]));
	memset(lru,-1,fno*sizeof(lru[0]));

	int cnt = 0;	// No of valid page in memory
	
	
	char c = fgetc(f);
	while(c != EOF){	// Iterates line by line

		int pno=0;		// current requested page
		char rw;		// memory acces type -> R/W

		c = fgetc(f);	// extracting page and R/W
		while(c != ' '){
			c = fgetc(f);
    			int k;
    			if((int)c < 58) k = (int)c - 48;
    			else k = ((int)c -97)+10;
    			if(k>-1 && k<16) pno = (pno<<4) + k;
		}
		pno = (pno>>12);
		c = fgetc(f);c = fgetc(f); rw = c;
		while(c != '\n') c = fgetc(f);
		c = fgetc(f);
		
		
		
		//////////////////////////////////////////////////////
		/////// Main Algorithms are implemented here//////////
		
		res[0]++;	// memory access
		
		// Check if page present -> Hit
		bool hit = false;
		for(int i=0;i<cnt;i++){
			if(phy_mem[i] == pno){
				hit = true;
				if(rw=='W' && !dirty[i]) dirty[i] = true;
				access[i] = true;
				swap(i,cnt,lru);
				break;
			}
		}
		if(!hit){
			res[1]++;	// MISS
			if(cnt<fno){	// Cold Miss
				phy_mem[cnt] = pno;
				if(rw=='W') dirty[cnt] = true;
				access[cnt] = true;
				lru[cnt] = cnt;
				cnt++;	// one page added
			}
			else if(!strcmp(stgy, "RANDOM")){	// Page Eviction
				
				if(ver) printf("Page 0x%05x was read from disk, ",pno);
				int lucky = (rand())%fno;
				if(dirty[lucky]) {
					res[2]++;
					if(ver) printf("page 0x%05x was written to the disk.\n",phy_mem[lucky]);
				}
				else {
					res[3]++;
					if(ver) printf("page 0x%05x was dropped (it was not dirty).\n",phy_mem[lucky]);
				}
				dirty[lucky] = (rw =='W');
				phy_mem[lucky] = pno;
			}
			else if(!strcmp(stgy, "FIFO")){	// Page Eviction
				if(ver) printf("Page 0x%05x was read from disk, ",pno);
				int lucky = (fifo_counter)%fno;
				fifo_counter++;
				if(dirty[lucky]) {
					res[2]++;
					if(ver) printf("page 0x%05x was written to the disk.\n",phy_mem[lucky]);
				}
				else {
					res[3]++;
					if(ver) printf("page 0x%05x was dropped (it was not dirty).\n",phy_mem[lucky]);
				}
				dirty[lucky] = (rw =='W');
				phy_mem[lucky] = pno;
			}
			else if(!strcmp(stgy, "CLOCK")){	// Page Eviction
				if(ver) printf("Page 0x%05x was read from disk, ",pno);
				while(access[clock_hand % fno]){
					access[clock_hand % fno]=false;
					clock_hand++;
				}
				int lucky = clock_hand % fno;
				access[lucky] = true;
				if(dirty[lucky]) {
					res[2]++;
					if(ver) printf("page 0x%05x was written to the disk.\n",phy_mem[lucky]);
				}
				else {
					res[3]++;
					if(ver) printf("page 0x%05x was dropped (it was not dirty).\n",phy_mem[lucky]);
				}
				dirty[lucky] = (rw =='W');
				phy_mem[lucky] = pno;
				clock_hand++;
			}
			else if(!strcmp(stgy, "LRU")){	// Page Eviction
				if(ver) printf("Page 0x%05x was read from disk, ",pno);
				int lucky = lru[0];
				swap(lru[0],cnt,lru);
				if(dirty[lucky]) {
					res[2]++;
					if(ver) printf("page 0x%05x was written to the disk.\n",phy_mem[lucky]);
				}
				else {
					res[3]++;
					if(ver) printf("page 0x%05x was dropped (it was not dirty).\n",phy_mem[lucky]);
				}
				dirty[lucky] = (rw =='W');
				phy_mem[lucky] = pno;
				lru[cnt-1]=lucky;
			}
			else{
				printf("ERROR : wrong input format\n");exit(1);
			}
		}
    		
    	///////////////End of Algorithm///////////////////////
	}
	
	fclose(f);
	
}

// Algorithm for optimal policy
void optimal(int* res, char fname[], int fno, bool ver){
	
	// Reading file
	FILE *f;
	f = fopen(fname,"r");
	if(f==NULL){ printf("Error! opening file\n"); exit(1);}
	
	int size = 0;
	char c = fgetc(f);
	while(c!=EOF){
		if(c=='\n') size++;
		c = fgetc(f);
	}

	fclose(f);
	f = fopen(fname,"r");

	int* page = malloc(size*sizeof(int));
	char* r_w = malloc(size*sizeof(char));
	c = fgetc(f);
	
	int z=0;
	while(c != EOF){
		int pno=0;
		char rw;
		c = fgetc(f);
		while(c != ' '){
			c = fgetc(f);
			//printf("%c",c);
			int k;
			if((int)c < 58) k = (int)c - 48;
			else k = ((int)c -97)+10;
			//printf("(%d) ",c);
			if(k>-1 && k<16) pno = (pno<<4) + k;
		}
		pno = (pno>>12);
		c = fgetc(f);c = fgetc(f); rw = c;
		while(c != '\n') c = fgetc(f);
		c = fgetc(f);

		page[z] = pno;
		r_w[z] = rw;
		//printf("0x%x %c -> 0x%x %c\n",pno,rw,page[z],r_w[z]);
		z++; 
	}


	int phy_mem[fno];
	bool dirty[fno];
	memset(dirty, 0, fno*sizeof(dirty[0]));
	memset(phy_mem, 0, fno*sizeof(phy_mem[0]));

	int cnt = 0;
	for(int j=0; j<size; j++){
		// Check if page present
		bool hit = false;
		for(int i=0;i<cnt;i++){
			if(phy_mem[i] == page[j]){
				hit = true;
				if(r_w[j]=='W' && !dirty[i]) dirty[i] = true;
				break;
			}
		}	
		if(!hit){
			res[1]++;	// miss
			if(cnt<fno){	// Cold Miss
				phy_mem[cnt] = page[j];
				if(r_w[j]=='W') dirty[cnt] = true;
				cnt++;	// one page added
			}
			else{
				int lucky;
				int lucky_idx = j-1;
				for(int i=0;i<fno;i++){
					int k;
					for(k=j+1;k<size;k++){
						if(page[k] == phy_mem[i]) {
							if(k>lucky_idx) {
								lucky_idx = k;
								lucky = i;
							}
							break;
						}
					}
					if(k==size){
						lucky = i; break;
						// if(lucky_idx == size){
						// 	if(phy_mem[lucky]>phy_mem[i]) lucky = i;
						// }
						// else{
						// 	lucky_idx = size;
						// 	lucky = i;
						// }
					}
				}
				if(ver) printf("Page 0x%05x was read from disk, ",page[j]);
				if(dirty[lucky]) {
					res[2]++;
					if(ver) printf("page 0x%05x was written to the disk.\n",phy_mem[lucky]);
				}
				else {
					res[3]++;
					if(ver) printf("page 0x%05x was dropped (it was not dirty).\n",phy_mem[lucky]);
				}
				dirty[lucky] = (r_w[j] =='W');
				phy_mem[lucky] = page[j];

			}
		}
	}
	res[0] = size;
	fclose(f);
}




int main(int argc, char* argv[]){

	char fname[256];
	int fno;
	bool ver = false;
	char stgy[10];
	
	// Parsing inputs
	// STD format --> ./a.out  trace.in 100 OPT -verbose
	if(argc == 5) ver = true;
	strcpy(fname, argv[1]);
	strcpy(stgy, argv[3]);
	fno = atoi(argv[2]);
	
	if(fno<1 || fno>max_no_of_frame
	|| (argc==5 && strcmp("-verbose", argv[4]) !=0) ) {
		printf("ERROR : wrong input format\n");
		exit(1);
	}
	
	// Output Array
	// Format : {memory_access, misses, writes, drops}
	int* out = malloc(4*sizeof(int));
	memset(out, 0, 4*sizeof(out[0]));
	
	
	if((!strcmp(stgy,"OPT"))) optimal(out, fname, fno, ver);
	else practical_policies(out, fname, fno, ver, stgy);
	// Printing Output
	printf("Number of memory accesses: %d\n",out[0]);
	printf("Number of misses: %d\n",out[1]);
	printf("Number of writes: %d\n",out[2]);
	printf("Number of drops: %d\n",out[3]);
	
	return 0;
}
