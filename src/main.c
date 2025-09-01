
#define FLAG_P 1
#define FLAG_Q 2
#define FLAG_R 4
#define FLAG_S 8

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int main( int argc, char **argv )
{
	(void)argc;
	(void)argv;
	char *line = NULL;
	int len = 0;
	get_next_line(&line, &len, 0);
	printf("%s\n", line);
	free(line);
	return (0);
}
