shell:
	gcc -o shell shell.c parse.c execute.c

clean:
	rm -f shell
