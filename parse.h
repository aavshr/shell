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
	char* ArgList[MAX_ARG_NUM];
	int argnum; 
} Command;

typedef struct{
	int boolInfile;  // if < parsed
	int boolOutfile; // if  > parsed
	int boolBackground; // run in background if & parsed
	//programs, multiple if | piped
	Command  ComArr[PIPE_MAX_NUM];
	int pipeNum; // number of pipes 
	char inFile[FILE_MAX_SIZE];
	char outFile[FILE_MAX_SIZE];
} parseInfo; 

parseInfo *parse(char *);
void free_info(parseInfo*);
void print_info(parseInfo*);

#endif