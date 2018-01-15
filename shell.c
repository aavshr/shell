#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parse.h"
//#include "builtins.c"

#define MAX_LINE_SIZE 256

static const char *progname = "shell";

int main(){
    int status = 1;
    char *cmd;
	char prompt[256];
	Command *com; 

	if(!getcwd(prompt, sizeof(prompt))){
		perror(progname);
		exit(1);
	}
	strcat(prompt,">> ");

    do{ 
    	cmd = readline(prompt);
      /* for Cntrl+D EOF */
      if(!cmd){
        return 0;
      }
      add_history(cmd);
    	com = parse(cmd);
  		//print_info(com);
  		status = execute(com);
  		free_info(com);
  	} while(status);
 
    return 0;
}
