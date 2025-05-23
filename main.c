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


int main(int ac, char **argv, char **envp)
{
	char        *line;
	t_token     *list = NULL;
	t_token     *tmp = NULL;
	t_command   *cmd_list = NULL;
	t_command	*cmd_tmp = NULL;
	int         parse_status;
	t_env **env;
	(void)ac;
	(void)argv;


	env = get_env(envp);
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
			tmp = tmp->next;
		}
		parse_status = start_parsing(list);
		if (parse_status == 1)
		{
			int ex = pars_command(list, &cmd_list);
			if (ex == 0)
				return (0);
			cmd_tmp = cmd_list;
			expand_var(list, cmd_list, env);
		}
		ft_exec(&cmd_tmp, env);
		free(line);
	}
	return (0);
}
