shell:
	gcc -Werror -o shell shell.c parse.c execute.c -lreadline

clean:
	rm -f shell
