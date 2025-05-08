/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:06 by asyani            #+#    #+#             */
/*   Updated: 2025/05/01 13:53:29 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char		*dup;
	size_t		len;
	size_t		i;

	len = strlen(s1);
	i = 0;
	dup = gc_malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


int main()
{
	char        *line;
	char        *type;
	t_token     *list = NULL;
	t_token     *tmp = NULL;
	t_command   *cmd_list = NULL;
	t_command   *cmd_tmp = NULL;
	int         parse_status;

	while (1)
	{
		list = NULL;
		cmd_list = NULL;

		line = readline("\033[1;32m minishell $ \033[0m");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		get_input(line, &list);
		tmp = list;
		while (tmp)
		{
			type = token_type(tmp);
			/*printf("%s[%d]: %s\n", type, tmp->type, tmp->content);*/
			tmp = tmp->next;
		}
		parse_status = start_parsing(list);
		if (parse_status == 1)
		{
			int ex = pars_command(list, &cmd_list);
			if (ex == 0)
				return (0);
			cmd_tmp = cmd_list;
			while (cmd_list)
			{
				int i = 0;
				while (cmd_list->argv && cmd_list->argv[i])
				{
					printf("argv[%d]: %s\n", i, cmd_list->argv[i]);
					i++;
				}
				if (cmd_list->infile)
					printf("infile: %s\n", cmd_list->infile);
				if (cmd_list->outfile)
					printf("outfile: %s\n", cmd_list->outfile);
				printf("append: %d\n", cmd_list->append);
				printf("------------\n");
				cmd_list = cmd_list->next;
			}
			cmd_list = cmd_tmp;
		}
		free(line);
	}
	return (0);
}
