#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parse.h"

static const char *progname = "shell";

int main(){
  int status = 1;
  char *cmd;
	char prompt[256];
	Command *com; 
  
  do{
    if(!getcwd(prompt, sizeof(prompt))){
        perror(progname);
        exit(1);
    }
    strcat(prompt,">> "); 
    cmd = readline(prompt);
    
    /* Ctrl+D or exit */
    if(!cmd || !strcmp(cmd,"exit")){
       exit(0);
    }
    add_history(cmd);
  	com = parse(cmd);
 		status = execute(com);
 		free_info(com);
 	} while(status);
 
  return 0;
}
