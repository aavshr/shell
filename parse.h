#ifndef __PARSE_H
#define __PARSE_H

#define MAX_ARG_NUM 10  
#define PIPE_MAX_NUM 10	
#define FILE_MAX_SIZE 40

/*	program = program to be executed
 *	ArgList = list of arguments to the program
 *	argum = number of arguments
 *  background = bool, if & parsed
 *  infile = bool, if < parsed
 *  outfile = bool, if > parsed
 *  inFileName = in file name
 *  outFileName = out file name;
*/
typedef struct {
	char* program;
	char* arglist[MAX_ARG_NUM];
	int argnum;
	int background;
	int infile;
	int outfile;
	char inFileName[FILE_MAX_SIZE];
	char outFileName[FILE_MAX_SIZE];
} SimpleCommand;

typedef struct{
	SimpleCommand*  ComTable[PIPE_MAX_NUM];
	int pipeNum; //number of pipes
} Command;

Command *parse(char *);
void free_info(Command*);
void print_info(Command*);
int execute(Command*);

/*
builtin function declaraions
*/
int cd(char **);
int help(char **);
int num_bultins(); // num of builtin functions

#endif