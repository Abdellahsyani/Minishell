/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:06 by asyani            #+#    #+#             */
/*   Updated: 2025/06/19 15:24:06 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_whitespace(char *str)
{
	int len;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n'))
		str[--len] = '\0';
	return str;
}


void ft_free_env(t_env **p)
{
	t_env *tmp;
	
	while (*p)
	{
		tmp = *p;
		(*p) = (*p)->next;
		free(tmp);
	}
	free(p);
}
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

	init_gc();
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	env = get_env(envp);
	update_exit_status(env, 0);
	while (1)
	{
		list = NULL;
		cmd_list = NULL;
		line = readline("minishell $ ");
		if (!line)
		{
			ft_free_env(env);
			gc_free_all();
			rl_clear_history();
			printf("exit\n");
			exit(0);
		}
		line = trim_whitespace(line);
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
			{
				free(line);
				return (0);
			}
			cmd_tmp = cmd_list;
			expand_var(cmd_list, env);
		}
		else
		{
			free(line);
			continue;
		}
		free(line);
		ft_exec(&cmd_tmp, env);
	}
	ft_free_env(env);
	gc_free_all();
	rl_clear_history();
}

