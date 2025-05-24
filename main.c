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

int main()
{
	char        *line;
	/*char	*type;*/
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
			token_type(tmp);
			/*printf("%s[%d]: %s\n", type, tmp->type, tmp->content);*/
			tmp = tmp->next;
		}
		parse_status = start_parsing(list);
		if (parse_status == 1)

		{

			int ex = pars_command(list, &cmd_list);
			if (ex == 0)
				return (0);
			expand_var(list, cmd_list);
			cmd_tmp = cmd_list;
			printf("\n<-------------------->\n");
			while (cmd_list)
			{
				int i = 0;
				/*while (cmd_list->argv_t && cmd_list->argv_t[i])*/
				/*{*/
				/*	printf("argv_t[%d]: %s\n", i, cmd_list->argv_t[i]);*/
				/*	i++;*/
				/*}*/
				/*printf("\n<---------<->---------->\n");*/
				/*i = 0;*/
				/*t_redi *r = cmd_list->redi;*/
				/*while (r)*/
				/*{*/
				/*					printf("==== %s == %d =\n", r->file, r->type);*/
				/*					r = r->next;*/
				/*}*/
				while (cmd_list->argv && cmd_list->argv[i])
				{
					printf("argv[%d]: %s\n", i, cmd_list->argv[i]);
					i++;
				}
				printf("------------\n");
				cmd_list = cmd_list->next;
			}
			printf("\n<-------------------->\n");
			cmd_list = cmd_tmp;
		}
		free(line);
	}
	return (0);
}
