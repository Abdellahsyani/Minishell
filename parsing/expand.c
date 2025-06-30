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

static void	expansion_spl(t_command *cmd, t_env **env, char **spl)
{
	int		i;
	char	*var;
	int		k;

	var = get_var(cmd->argv_t[0], env, 1);
	if (!var)
		return ;
	spl = ft_split(var, ' ');
	i = 0;
	while (spl[i])
		i++;
	if (cmd->argv_t[1])
	{
		k = 1;
		while (cmd->argv_t[k])
		{
			k++;
			i++;
		}
	}
	hanlde_allafter_var(cmd, spl, env, i);
}

static int	h_export(t_command *cmd, t_env **env)
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

int	checks_token(const char *str)
{
	int i = 0;
	int found_single = 0, found_double = 0;
	char in_quote = 0;

	while (str[i])
	{
		if (!in_quote && (str[i] == '"' || str[i] == '\''))
		{
			in_quote = str[i];
			if (in_quote == '"')
				found_double = 1;
			else
				found_single = 1;
		} else if (in_quote && str[i] == in_quote)
			in_quote = 0;
		i++;
	}
	return (found_single && found_double);
}

char	*get_con(char *content, char del, int *i)
{
	int	start = *i;
	int	len = 1;
	char	*var = NULL;

	(*i)++;
	while (content[*i])
	{
		if (content[*i] == del)
		{
			len++;
			break ;
		}
		(*i)++;
		len++;
	}
	var = ft_strlcpy(NULL, content, len, start);
	return (var);
}

char	*get_var2(char *str, int *i)
{
	int	start = *i;
	int	len = 0;
	char *var = NULL;
	while(str[*i])
	{
		if (!ft_isalnum(str[*i]))
			break;
		(*i)++;
		len++;
	}	
	var = ft_strlcpy(var, str, len, start);
	return (var);
}

char	*get_simple(char *content, int *i)
{
	char	*var;
	int	start = *i;
	int	len = 0;

	while (content[*i])
	{
		if (content[*i] == '"' || content[*i] == '\'' || content[*i] == '$')
		{
			(*i)--;
			break ;
		}
		if (content[*i + 1] == '\0')
		{
			len++;
			break ;
		}
		(*i)++;
		len++;
	}
	var = ft_strlcpy(NULL, content, len, start);
	return (var);
}

char	*ft_fill(char *content, t_env **env, char del, int *i)
{
	char *var;
	char	*str;

	str = NULL;
	var = NULL;
	if (del == '"')
	{
		var = get_con(content, '"', i);
		str = double_quote(var, env);
	}
	else if (del == '\'')
	{
		var = get_con(content, '\'', i);
		str = single_quote(var);
	}
	else if (del == '$')
	{
		var = get_var2(content, i);
		str = get_var(var, env, 1);
	}
	return (str);
}

char	*split_args(char *content, t_env **env)
{
	int	i = 0;
	char *var;
	char	*join;

	join = NULL;
	while (content[i])
	{
		var = NULL;
		if (content[i] == '"')
			join = ft_strjoin(join, ft_fill(content, env, '"', &i));
		else if (content[i] == '\'')
			join = ft_strjoin(join, ft_fill(content, env, '\'', &i));
		else if (content[i] == '$')
			join = ft_strjoin(join, ft_fill(content, env, '$', &i));
		else
		{
			var = get_simple(content, &i);
			join = ft_strjoin(join, var);
		}
		i++;
	}
	return (join);
}

static void	fill_argvs(t_command *cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd->argv_t[i])
	{
		if (checks_token(cmd->argv_t[i]) == 1)
		{
			cmd->argv[i] = split_args(cmd->argv_t[i], env);
			i++;
			continue ;
		}
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

static void	c_alloc(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd->argv_t[count])
		count++;
	cmd->argv = gc_malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
		return ;
}

int	expand_var(t_command *cmd, t_env **env)
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
		if (!count_quotes(env))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
