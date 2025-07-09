/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:41:19 by asyani            #+#    #+#             */
/*   Updated: 2025/07/01 15:22:33 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_con(char *content, char del, int *i)
{
	int		start;
	int		len;
	char	*var;

	start = *i;
	len = 1;
	var = NULL;
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

static char	*get_var2(char *str, int *i)
{
	int		start;
	int		len;
	char	*var;

	start = *i;
	len = 0;
	var = NULL;
	while (str[*i])
	{
		if (!ft_isalnum(str[*i]))
			break ;
		(*i)++;
		len++;
	}
	var = ft_strlcpy(var, str, len, start);
	return (var);
}

static char	*get_simple(char *content, int *i)
{
	char	*var;
	int		start;
	int		len;

	start = *i;
	len = 0;
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

static char	*ft_fill(char *content, t_env **env, char del, int *i)
{
	char	*var;
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
	int		i;
	char	*var;
	char	*join;

	i = 0;
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
		if (content[i] == '\0')
			break ;
		i++;
	}
	return (join);
}
