/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:27:50 by asyani            #+#    #+#             */
/*   Updated: 2025/06/25 18:28:06 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_vars(t_command *cmd, t_env **env, int *flag, int *j)
{
	int	i;

	(*flag) = 0;
	i = 1;
	while (cmd->argv_t[i])
	{
		if (cmd->argv_t[i][0] == '\'')
			cmd->argv[*j] = single_quote(cmd->argv_t[i]);
		else if (cmd->argv_t[i][0] == '"')
			cmd->argv[*j] = double_quote(cmd->argv_t[i], env);
		else if (cmd->argv_t[i][0] == '$' && (ft_isalnum(cmd->argv_t[i][1])
			|| cmd->argv_t[i][1] == '_' || cmd->argv_t[i][1] == '?'))
			cmd->argv[*j] = get_var(cmd->argv_t[i], env, 1);
		else
			cmd->argv[*j] = copy_var(cmd->argv_t[i], env, 0);
		i++;
		(*j)++;
	}
}

static void	fill_after_var(t_command *cmd, int *j)
{
	int	i;

	i = 1;
	while (cmd->argv_t[i])
	{
		cmd->argv[*j] = ft_strdup(cmd->argv_t[i]);
		(*j)++;
		i++;
	}
}

void	hanlde_allafter_var(t_command *cmd, char **spl, t_env **env, int i)
{
	int	flag;
	int	j;

	j = 0;
	flag = 1;
	cmd->argv = gc_malloc(sizeof(char *) * (i + 1));
	if (!cmd->argv)
		return ;
	if (spl[0])
	{
		i = 0;
		while (spl[i])
		{
			cmd->argv[j] = ft_strdup(spl[i]);
			i++;
			j++;
		}
	}
	else
		expand_vars(cmd, env, &flag, &j);
	if (flag == 1)
		fill_after_var(cmd, &j);
	cmd->argv[j] = NULL;
	free_2d(spl);
}

int	get_all_var(char *str, int *i)
{
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		if (ft_isdigit(str[1]))
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	return (*i);
}

int	count_quotes(t_env **env)
{
	if (g_global->count_single % 2 != 0 || g_global->count_double % 2 != 0)
	{
		ft_putstr_fd("minishell: error: unexpected quote\n", 2);
		update_exit_status(env, 2);
		return (0);
	}
	return (1);
}
