/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:51:37 by asyani            #+#    #+#             */
/*   Updated: 2025/06/21 18:49:11 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expansion_spl(t_command *cmd, t_env **env, char **spl)
{
	int		i;
	int		j;
	char	*var;

	var = get_var(cmd->argv_t[0], env, 1);
	if (!var)
		return ;
	spl = ft_split(var, ' ');
	i = 0;
	j = 0;
	int flag = 1;
	while (spl[i])
		i++;
	if (cmd->argv_t[1])
	{
		int k = 1;
		while (cmd->argv_t[k])
		{
			k++;
			i++;
		}
	}
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
	{
		flag = 0;
		i = 1;
		while (cmd->argv_t[i])
		{
			if (cmd->argv_t[i][0] == '\'')
				cmd->argv[j] = single_quote(cmd->argv_t[i]);
			else if (cmd->argv_t[i][0] == '"')
				cmd->argv[j] = double_quote(cmd->argv_t[i], env);
			else if (cmd->argv_t[i][0] == '$' && (ft_isalnum(cmd->argv_t[i][1])
				|| cmd->argv_t[i][1] == '_' || cmd->argv_t[i][1] == '?'))
				cmd->argv[j] = get_var(cmd->argv_t[i], env, 1);
			else
				cmd->argv[j] = copy_var(cmd->argv_t[i], env, 0);
			i++;
			j++;
		}
	}
	if (flag == 1)
	{
		i = 1;
		while (cmd->argv_t[i])
		{
			cmd->argv[j] = ft_strdup(cmd->argv_t[i]);
			j++;
			i++;
		}
	}
	cmd->argv[j] = NULL;
	free_2d(spl);
}

int	h_export(t_command *cmd, t_env **env)
{
	char	**spl;
	char	*ex;

	spl = NULL;
	if (cmd->argv_t[0][0] == '"' && cmd->argv_t[0][1] == '$')
	{
		ex = double_quote(&cmd->argv_t[0][0], env);
		failure_alloc(cmd, ex);
		return (0);
	}
	if (cmd->argv_t[0][0] == '$')
	{
		if (cmd->argv_t[0][0] == '$' && cmd->argv_t[0][1] == '\0')
		{
			failure_alloc(cmd, NULL);
			return (0);
		}
		expansion_spl(cmd, env, spl);
	}
	free_2d(cmd->argv_t);
	return (1);
}

void	fill_argvs(t_command *cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd->argv_t[i])
	{
		if (cmd->argv_t[i][0] == '\'')
			cmd->argv[i] = single_quote(cmd->argv_t[i]);
		else if (cmd->argv_t[i][0] == '"')
			cmd->argv[i] = double_quote(cmd->argv_t[i], env);
		else if (cmd->argv_t[i][0] == '$' && (ft_isalnum(cmd->argv_t[i][1])
			|| cmd->argv_t[i][1] == '_' || cmd->argv_t[i][1] == '?'))
			cmd->argv[i] = get_var(cmd->argv_t[i], env, 1);
		else
			cmd->argv[i] = copy_var(cmd->argv_t[i], env, 0);
		i++;
	}
	cmd->argv[i] = NULL;
}

void	c_alloc(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd->argv_t[count])
		count++;
	cmd->argv = gc_malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
		return ;
}

void	expand_var(t_command *cmd, t_env **env)
{
	while (cmd)
	{
		if (!cmd->argv_t || !cmd->argv_t[0])
		{
			cmd = cmd->next;
			continue ;
		}
		c_alloc(cmd);
		if (cmd->argv_t[0][0] == '$' || (cmd->argv_t[0][0] == '"'
				&& cmd->argv_t[0][1] == '$'))
		{
			h_export(cmd, env);
			if (cmd->next)
			{
				cmd = cmd->next;
				continue ;
			}
			break ;
		}
		fill_argvs(cmd, env);
		cmd = cmd->next;
	}
}
