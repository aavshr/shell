#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

#define MAXLINE 65
#define TOKEN_BUF_SIZE 64
#define TOKEN_DELIM " \n\t\r\a"

static const char *progname = "shell";

void init_info(parseInfo *p){
	int i;
	p->boolInfile = 0; 
	p->boolOutfile = 0;
	p->boolBackground = 0;
	for(i=0;i<PIPE_MAX_NUM;i++){
		(p->CommArr[i])->argnum = 0;
	}
	p->pipeNum = 0;
}

void parse_command(char** cmd, Command *comArr, int cmd_size, int cmd_index){
	int i;
	comArr[cmd_index]->program = cmd[0];
	comArr[cmd_index]->argnum = size-1;

	if (argnum == 0) {
		comArr[cmd_Index]->ArgList = NULL;
 	}
 	else {
 		for(i=0;i<argnum;i++){
 			comArr[cmd_index]->ArgList[i] = cmd[i+1]; 
 		}
 	}
}

parseInfo *parse(char* cmdLine){
	parseInfo *result;
	init_info(result);

	char *token, **tokens, **cmd; 
	int buf_size = TOKEN_BUF_SIZE, tokens_size = 0; //tokens size
	int i, cmd_size = 0, cmd_index = 0;

	tokens = malloc(*sizeof(char*)*bufsize);

	if(!tokens){
		perror(progname);
		exit(1);
	}

	/*
	read character by character here
	tokenize only in the parse_command function
	should be more easier
	*/

	token = strtok(cmdLine, LSH_TOK_DELIM);

	while(token!=NULL){
		tokens[tokens_size] = token;
		tokens_size++;

		if (tokens_size >= buf_size){
			bufsize += TOKEN_BUF_SIZE;
			tokens = realloc(tokens, buf_size*sizeof(char*));
			if(!tokens){
				free(tokens);
				free_info(Result);
				perror(progname);
				exit(1);
			}
		}

		token = (NULL, TOKEN_DELIM);
	}
	tokens[tokens_size] = NULL;

	cmd = malloc(sizeof(char*) * tokens_size);
	
	for(i=0;i<tokens_size;i++){
		if(!strcmp(tokens[i],"<\0")){
			parse_command(cmd, result->ComArr, cmd_size, cmd_index);
			result->boolInfile = 1;
			inFile = token[i+1];
		}
		if(!strcmp(tokens[i],">\0")){
			parse_command(cmd, result->ComArr, cmd_size, cmd_index);
			result->boolOutfile = 1; 
			outfile = token[i+1];
		}

		if(!strcmp(tokens[i],"|\0")){
			cmd_index = 1; 
		}
	}
}

void print_info(parseInfo* p){
	
}

void free_info(parseInfo* p){

}
