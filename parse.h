#ifndef __PARSE_H
#define __PARSE_H

#define MAX_ARG_NUM 10  //maximum arguments
#define PIPE_MAX_NUM 10	 //maximum pipes
#define FILE_MAX_SIZE 40  //maximum file name size

/*	program = program to be executed
 *	ArgList = list of arguments to the program
 *	argum = number of arguments
 *  background = if & parsed
 *  infile = if < parsed
 *  outfile = if > parsed
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
	SimpleCommand*  ComTable[PIPE_MAX_NUM]; // array of simple command pointers
	int pipeNum; //number of pipes
} Command; 

Command *parse(char *);
void free_info(Command*);
void print_info(Command*);
int execute(Command*);

#endif