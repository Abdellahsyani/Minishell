#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>

int main()
{
	char *line;
	while (1)
	{
		line = readline("$ ");
		printf("%s\n", line);
	}
	return (0);
}
