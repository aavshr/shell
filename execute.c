#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "parse.h"

static const char* progname = "shell";

int execute(Command *c){
	pid_t pid; 
	int i,j,k,status;
	int prog_num = c->pipeNum+1;
	int first_child = 0, last_child = 0;
	FILE *in, *out;
	char buffer[256];

	char* args[prog_num][c->ComTable[0]->argnum+2];
	
	for(i=0;i<prog_num;i++){
		args[i][0] = c->ComTable[i]->program;
		
		for(j = 1; j < (c->ComTable[i]->argnum+1);j++)
			args[i][j] = c->ComTable[i]->arglist[j-1];
		
		args[i][c->ComTable[0]->argnum+1] = (char*) NULL;
	}

	int fds[2*c->pipeNum], io[2]; 
	for(i =0; i <(c->pipeNum);i++){
		if(pipe(fds + i*2) < 0){
			perror("initial pipe");
			exit(1);
		}
	}

	j = 0;
	for(i = 0;i<prog_num;i++){
		if(i==(prog_num-1)) last_child = 1; 
		if(i>0) first_child = 0;
		
		pid = fork();
		
		if(pid<0){
			perror(progname);
			exit(1);
		}

		else if(pid == 0){
			if(c->ComTable[i]->infile){
				close(0);
				if(open(c->ComTable[i]->inFileName, O_RDONLY) < 0){
					perror(progname);
					exit(1);
				}
			}

			if(c->ComTable[i]->outfile){
				close(1);
				fopen(c->ComTable[i]->outFileName, "w");
				if(open(c->ComTable[i]->outFileName, O_WRONLY|O_TRUNC) < 0){
					perror(progname);
					exit(1);
				}
			}

			if(!first_child && prog_num > 1){
				if(dup2(fds[j-2],STDIN_FILENO) < 0){
					perror("not first child");
					exit(1);
				}
			}

			if(!last_child && prog_num > 1){
				if(dup2(fds[j+1],STDOUT_FILENO)<0){
					perror("not last child");
					exit(1);
				}	
			}

			for(k = 0; k < 2*(c->pipeNum); k++){
                close(fds[k]);
            }

            if(c->ComTable[i]->background){
            	daemon(1,1);
            }
			execvp(args[i][0],args[i]);
			perror(args[i][0]);
			exit(1);
		}
		j+=2;
	}

	for(k=0;k<2*(c->pipeNum);k++){
			close(fds[k]);
	}	

	for(k=0;k<prog_num;k++){
		wait(&status);
	}
		
	return 1;
}