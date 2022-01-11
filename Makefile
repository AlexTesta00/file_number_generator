CFLAG = -ansi -Wall -Wpedantic -Werror

generator:		generator.c
				gcc ${CFLAG} generator.c -o generator