#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

#define MAX_LINE_SIZE 256
#define TOKEN_BUF_SIZE 128
#define SIMPLE_DELIM "<>& \n"
#define PIPE_DELIM "|"

static const char *progname = "shell";

void init_info(Command *p){
	int i;
	p->infile = 0; 
	p->outfile = 0;
	p->background = 0;
	
	for(i=0;i<PIPE_MAX_NUM;i++){
		p->ComTable[i] = malloc(sizeof(SimpleCommand));
		if(!(p->ComTable[i])){
			perror(progname);
			exit(1);
		}
		(p->ComTable[i])->argnum = 0;
	}
	
	for(i=0;i<MAX_ARG_NUM;i++){
		p->ComTable[i]->arglist[i] = malloc(sizeof(char*));
	}
	p->pipeNum = 0;
}

void parse_command(char *cmd, Command *p, int com_num){
	int i=0, toksize = TOKEN_BUF_SIZE, count = 0;
	char **tokens = malloc(sizeof(char*) * toksize);
	char *token; 
	
	if(!tokens){
		perror(progname);
		exit(1);
	}

	if(strchr(cmd, '<')) p->infile = 1;
	if(strchr(cmd, '>')) p->outfile = 1;
	if(strchr(cmd, '&')) p->background = 1;

	token = strtok(cmd, SIMPLE_DELIM);
	while(token != NULL){
		tokens[count] = token; 
		//printf("simple tokens[%d]: %s\n", count, tokens[count]);
		count++;
		if(count >= toksize){
			toksize += TOKEN_BUF_SIZE;
			tokens = realloc(tokens, toksize * sizeof(char*)); 
			if(!tokens){
			perror(progname);
			exit(1);
			}
		}
		token = strtok(NULL, SIMPLE_DELIM);
	}

	if(!p->infile && !p->outfile && !p->background){
		p->ComTable[com_num]->program = tokens[i++];
		while(i<count){
			p->ComTable[com_num]->arglist[i-1] = tokens[i++];
			p->ComTable[com_num]->argnum++;
		}
	}

	if(p->infile && !p->outfile){
		//puts("has infile\n");
		strcpy(p->inFile,tokens[0]);
		//printf("Infile: %s", p->inFile);
		i = 1;
		p->ComTable[com_num]->program = tokens[i++];
		while(i<(count-1)){
			p->ComTable[com_num]->arglist[i-1] = tokens[i++];
			p->ComTable[com_num]->argnum++;
		}
	}
	if(p->outfile && !p->infile){
		p->ComTable[p->pipeNum]->program = tokens[0];
		i = 1;
		while(i<(count)-1){
			p->ComTable[com_num]->arglist[i-1] = tokens[i++];
			p->ComTable[com_num]->argnum++;
		}
		strcpy(p->outFile, tokens[count-1]);
	}
	if(p->background){
		p->ComTable[com_num]->program = tokens[0];
		i=1;
		while(i<count){
			p->ComTable[com_num]->arglist[i-1] = tokens[i++];
			p->ComTable[com_num]->argnum++;
		}
	}
}

Command *parse(char* cmdLine){
	int i,j = 0, pipe_num = 0, count = 0;
	char *c, *token, **tokens;

	Command *result;
	init_info(result);

	c = cmdLine; 
	
	while(*c !='\0' && *c !='\n'){
		if(*c == '|'){
			pipe_num++;
		}
		c++;
	}
	result->pipeNum = pipe_num;
	
	if (pipe_num == 0){
		//printf("cmd: %s", cmdLine);
		parse_command(cmdLine, result, 0);
	}
	else{
		int toksize = pipe_num+1;
		tokens = malloc(sizeof(char*)* toksize);
		if(!tokens){
			perror(progname);
			exit(1);
		}
		token = strtok(cmdLine, PIPE_DELIM);
		while(token != NULL){
			tokens[count] = token;
			count++;
			token = strtok(NULL, PIPE_DELIM);
		}
		for(i=0;i<count;i++){
			//printf("cmd_tokens[%d]: %s \n", i, tokens[i]);
			parse_command(tokens[i], result, i);
		}
	}
	free(tokens);
	return result;
}

void print_info(Command* p){
	int i,j;

	printf("infile: %d, outfile: %d, background: %d\n",p->infile, p->outfile, p->background);
	printf("pipenum: %d\n", p->pipeNum);
	if(p->infile == 1) printf("infile: %s", p->inFile);
	if(p->outfile == 1) printf("outfile: %s", p->outFile);
	
	for(i=0;i < (p->pipeNum+1);i++){
		printf("\nprogram[%d]: %s, ",i, p->ComTable[i]->program);
		printf("total arguments = : %d\n", p->ComTable[i]->argnum);
		for(j=0;j<(p->ComTable[i]->argnum);j++) 
			printf("arguments[%d]: %s\n",j, p->ComTable[i]->arglist[j]);
	}
	return;	
}

void free_info(Command* p){
	int i,j;
		
	for(i=0;i<p->pipeNum;i++){
		for(j=0;j<p->ComTable[i]->argnum;j++){
			free(p->ComTable[i]->arglist[j]);
		}
		free(p->ComTable[i]);
	}
}

