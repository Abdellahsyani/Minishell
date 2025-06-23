/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:06 by asyani            #+#    #+#             */
/*   Updated: 2025/06/23 11:04:31 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_whitespace(char *str)
{
	int	len;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len
			- 1] == '\n'))
		str[--len] = '\0';
	return (str);
}

void	ft_free_env(t_env **p)
{
	t_env	*tmp;

	while (*p)
	{
		tmp = *p;
		(*p) = (*p)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(p);
}

void	clean_all(t_env **env, int n, int flag)
{
	ft_free_env(env);
	gc_free_all();
	rl_clear_history();
	if (flag)
		write(2, "exit\n", 5);
	exit(n);
}

void	program_run(t_env **env)
{
	char		*line;
	t_token		*list;
	t_token		*tmp;
	t_command	*cmd_list;
	t_command	*cmd_tmp;
	int			parse_status;

	list = NULL;
	tmp = NULL;
	cmd_list = NULL;
	cmd_tmp = NULL;
	while (1)
	{
		list = NULL;
		cmd_list = NULL;
		if (!g_global)
			init_gc();
		line = readline("minishell $ ");
		if (!line)
			clean_all(env, 1, 1);
		line = trim_whitespace(line);
		if (!*line && line)
			continue ;
		if (*line)
			add_history(line);
		get_input(line, &list);
		tmp = list;
		token_type(tmp);
		parse_status = start_parsing(list, env);
		if (parse_status == 1)
		{
			pars_command(list, &cmd_list, env);
			cmd_tmp = cmd_list;
			expand_var(cmd_list, env);
		}
		else
		{
			free(line);
			continue ;
		}
		free(line);
		ft_exec(&cmd_tmp, env);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_env	**env;

	(void)ac;
	(void)argv;
	init_gc();
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	env = get_env(envp);
	update_exit_status(env, 0);
	program_run(env);
	clean_all(env, 0, 0);
}
