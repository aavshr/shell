#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

char* read_cmd(){
	char* command; 
	ssize_t cmd_size; 
	getline(&command, &cmd_size, stdin);
	return command;
}

char* parse_cmd(){

}


int main(){
	char* line; 

	line = read_cmd();

	printf("%s", line);
	return 0;
}