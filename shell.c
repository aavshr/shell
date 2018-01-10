#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
//#include "parse.h"
//#include "builtins.c"
//#include "execute.c"

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

char* read_cmd(){
	char* cmd;
	ssize_t cmd_size; 
	getline(&cmd, &cmd_size, stdin);
	return cmd;
}

int main(){
    int status = 1;
    char* cmd; 
    char** prog;

    do{
    printprompt();
    cmd = read_cmd();
    printf("%s", cmd);
  	} while(status);
 
    return 0;
}
