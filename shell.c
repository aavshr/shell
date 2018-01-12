#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "parse.h"
//#include "builtins.c"
//#include "execute.c"

#define MAX_LINE_SIZE 256

static const char *progname = "shell";

void printprompt(){
	char cwd[256];
	if(getcwd(cwd, sizeof(cwd)))
		printf("%s:$ ",cwd);
	else {
		perror(progname);
		exit(1);
	} 
}

int main(){
    int status = 1;
    char cmd[MAX_LINE_SIZE]; 
	
	Command* com;  
    
    do{
    	printprompt();
    	fgets(cmd, MAX_LINE_SIZE, stdin); 
    	com = parse(cmd);
  		print_info(com);
  		free_info(com);
  	} while(status);
 
    return 0;
}
