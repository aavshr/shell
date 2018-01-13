#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

static const char* progname = "shell";

int execute(Command *c){
	pid_t pid; 
	int i,status;

	char* args[c->ComTable[0]->argnum+2];
	args[0] = c->ComTable[0]->program;

	for(i = 1; i < (c->ComTable[0]->argnum+1);i++){
		args[i] = c->ComTable[0]->arglist[i-1];
	}

	args[c->ComTable[0]->argnum+1] = (char*) NULL;

	pid = fork();
	if(pid<0){
		perror(progname);
		exit(1);
	}
	else if(pid == 0){
		execvp(args[0],args);
		perror(progname);
		exit(1);
	}
	
	else{
		waitpid(pid, &status, 0);
	}
	return 1;
}