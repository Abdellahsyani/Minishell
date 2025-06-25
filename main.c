/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:06 by asyani            #+#    #+#             */
/*   Updated: 2025/06/25 17:11:33 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_program(char *line, t_token **list)
{
	t_token	*tmp;

	tmp = NULL;
	g_global->count_quote = 0;
	if (*line)
		add_history(line);
	get_input(line, list);
	tmp = *list;
	token_type(tmp);
}

int	norm1_p_run(t_token *list, t_command **tmp, t_command *cmd, t_env **env)
{
	if (start_parsing(list, env))
	{
		if (!pars_command(list, &cmd, env))
			return (0);
		*tmp = cmd;
		expand_var(cmd, env);
		return (1);
	}
	return (0);
}

void	program_run(t_env **env, char *line, t_command *cmd_list, t_token *list)
{
	t_command	*cmd_tmp;

	cmd_tmp = NULL;
	while (1)
	{
		list = NULL;
		cmd_list = NULL;
		if (!g_global)
			init_gc();
		line = readline("minishell $ ");
		line = trim_whitespace(line);
		if (!line)
			clean_all(env, 1, 1);
		if (!*line && line)
			continue ;
		norm_program(line, &list);
		if (!norm1_p_run(list, &cmd_tmp, cmd_list, env))
		{
			gc_free_one(line);
			continue ;
		}
		gc_free_one(line);
		ft_exec(&cmd_tmp, env);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_env		**env;
	char		*line;
	t_command	*cmd_list;
	t_token		*list;

	(void)ac;
	(void)argv;
	line = NULL;
	cmd_list = NULL;
	list = NULL;
	init_gc();
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	env = get_env(envp);
	update_exit_status(env, 0);
	program_run(env, line, cmd_list, list);
	clean_all(env, 0, 0);
}
