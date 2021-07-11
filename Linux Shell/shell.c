/*
	Author : 	Vivek Muskan (2017MT10755)
	Description : 	This code develops a simpler shell similar to bash 				shell of linux.
	Commands Supported : 	All executable commmands, cd and history 
	Contact/Help : 	mt1170755@iitd.ac.in
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024	// Maximum size of whole input line in no. of char
#define MAX_NO_OF_ARGS 20	// Maxinum no. of arguments passed in input (splitted with white space)
#define MAX_ARGS_SIZE 256	// Maximum size of any argument passed

int main(int argc, char *argv[]){

	char h[5][MAX_INPUT_SIZE] = {"","","","",""};	// Storing command history
	
	// Getting home dir
	char home[MAX_INPUT_SIZE]="";
	getcwd(home,MAX_INPUT_SIZE);
	
	// Loop Starts
	while(1){
	
		// Getting current dir
		char cwd[MAX_INPUT_SIZE]="";
		getcwd(cwd,MAX_INPUT_SIZE);
		printf("MTL458:");
		
		// Formatting current path (Applying "~" notation)
		if(strcmp(home, cwd) == 0) printf("~$ ");
		else if(strlen(cwd) > strlen(home)){
			char c[MAX_INPUT_SIZE] = "";
			strncpy(c, cwd, strlen(home));
	
			if(strcmp(c, home) == 0) {
				printf("~");
				char c1[MAX_INPUT_SIZE]="";
				strncpy(c1, cwd+strlen(home), (strlen(cwd) - strlen(home)));
				printf("%s$ ",c1);
			}
			else printf("%s$ ",cwd);
		}
		else printf("%s$ ",cwd);

		// Reading commands from user	
		size_t size  = MAX_INPUT_SIZE;		
		char *inp;
		inp = (char *) malloc (size);
		int c =  getline(&inp,&size,stdin);
		if(inp[0] == '\n') continue;
   		
		// Keeping history track
		strcpy(h[0],h[1]);
		strcpy(h[1],h[2]);
		strcpy(h[2],h[3]);
		strcpy(h[3],h[4]);
		strcpy(h[4],inp);
			
		// Splitting Commands
		char args[MAX_NO_OF_ARGS][MAX_ARGS_SIZE] = {};
		int i = 0;
		int j = 0;
		while(inp[i] != '\n'){
			if( inp[i] == ' ') j++;
		   	else strncat( args[j], &inp[i], 1);
		   	i++;
		}
		j++;
		
		// HISTORY
		if(!strcmp(args[0],"history")){
		   	if(strlen(args[1]) > 0) fprintf(stderr,"bash: history: too many arguments\n");
		   	else{
		   		for(int k=0; k<5; k++){
		   			if(strlen(h[k])>0) printf("%s", h[k]);
	   			}
	   		}
	   	}
	   	
	   	// CD -> chdir()
	   	else if(!strcmp(args[0],"cd")){
	   		//printf("Not Yet Done\n");
	   		char mypwd[MAX_INPUT_SIZE];
	   		if(strlen(args[2])>0) fprintf(stderr,"bash: cd: too many arguments\n");
	   		else if(strlen(args[1])==0 || strcmp(args[1],"~")==0) chdir(home);
	   		else if(chdir(args[1]) != 0) fprintf(stderr,"bash: chdir(): %s --> %s failed\n",getcwd(mypwd, 1024), args[1]);
	   		else continue;
	   		
	   	}
	   	// General Executable Commands - ls, clear, cat, echo, sleep
		else{
			int rc = fork();
			
			if(rc<0){
				fprintf(stderr,"Fork Failed\n");
				exit(1);
			}
			else if(rc == 0){
			   	
				char *myargs[j+1];
				for(int k=0; k<j; k++){
					myargs[k] = strdup(args[k]);
				}
				myargs[j] = NULL;
				execvp(myargs[0],myargs);
					
				fprintf(stderr,"%s : command not found\n",args[0]);
				exit(1);
			}
			else{
				int wc = wait(NULL);
			}
		}
	}
	return 0;
}
