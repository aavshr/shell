#ifndef __PARSE_H
#define __PARSE_H

#define MAX_ARG_NUM 10  //maximum arguments
#define PIPE_MAX_NUM 10	 //maximum pipes
#define FILE_MAX_SIZE 40  //maximum file name size

/*	program = program to be executed
 *	ArgList = list of arguments to the program
 *	argum = number of arguments
*/
typedef struct {
	char* program;
	char* arglist[MAX_ARG_NUM];
	int argnum; 
} SimpleCommand;

typedef struct{
	int infile;  // if < parsed
	int outfile; // if  > parsed
	int background; // run in background if & parsed
	SimpleCommand*  ComTable[PIPE_MAX_NUM];
	int pipeNum; // number of pipes 
	char inFile[FILE_MAX_SIZE];
	char outFile[FILE_MAX_SIZE];
} Command; 

Command *parse(char *);
void free_info(Command*);
void print_info(Command*);

#endif