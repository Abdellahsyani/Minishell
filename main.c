/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:06 by asyani            #+#    #+#             */
/*   Updated: 2025/06/04 15:45:05 by abhimi           ###   ########.fr       */
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

	
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	gc_type(1, e_dont_free);
	env = get_env(envp);
	update_exit_status(env, 0);
	gc_type(1, e_free_content);
	while (1)
	{
		list = NULL;
		cmd_list = NULL;

		line = readline("\033[1;32mminishell $ \033[0m");
		
		if (!line)
		{
			gc_type(1, e_free_all);
			//ft_free_gc();
			printf("exit\n");
			break;
		}
		if (!*line && line)
			continue ;
		if (*line)
			add_history(line);
		get_input(line, &list);
		tmp = list;
		while (tmp)
		{
			token_type(tmp);
			tmp = tmp->next;
		}
		
		parse_status = start_parsing(list, env);
		
		if (parse_status == 1)
		{
			
			int ex = pars_command(list, &cmd_list);
			if (ex == 0)
				return (0);
			cmd_tmp = cmd_list;
			expand_var(cmd_list, env);
		}
		else
		{
			free(line);
			continue;
		}
			
		//printf("here");
		ft_exec(&cmd_tmp, env);
		//ft_free_gc();
		free(line);
		//ft_free_gc();
	}
	gc_type(1, e_free_all);
	// ft_free_gc();
	
}
