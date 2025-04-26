#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include <readline/history.h>

int main()
{

	char *line;
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
			add_history(line);
		printf("%s\n", line);
	}
	return (0);
}
