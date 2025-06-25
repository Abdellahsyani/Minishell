/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:04 by asyani            #+#    #+#             */
/*   Updated: 2025/06/21 18:47:21 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*stcopy(char *var, char *content, char del)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == del)
		{
			i++;
			continue ;
		}
		var[count] = content[i];
		count++;
		i++;
	}
	var[count] = '\0';
	return (var);
}

char	*ft_get(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp((tmp)->key, key))
			return (tmp->value);
		(tmp) = (tmp)->next;
	}
	return (NULL);
}

char	*get_status(char *str, t_env **env, int i, int j)
{
	char	*var;
	char	*exp;
	char	*last;

	last = gc_malloc(sizeof(char) * ft_strlen(str));
	if (!last)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '?')
			exp = ft_strdup("?");
		else
		{
			last[j] = str[i];
			j++;
		}
		i++;
	}
	last[j] = '\0';
	var = ft_strdup(ft_get(env, exp));
	if (last)
		var = ft_strjoin(var, last);
	return (var);
}

char	*get_var1(char *str)
{
	char	*var;
	int		i;
	int		start;
	int		len;

	i = 1;
	len = 0;
	start = 0;
	var = NULL;
	start = i;
	while (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?' || ft_isdigit(str[i]))
	{
		if (ft_isdigit(str[i]))
		{
			i++;
			break ;
		}
		if (str[i] == ' ' || str[i] == '"')
			break ;
		i++;
	}
	len = i - 1;
	var = ft_strlcpy(var, str, len, start);
	return (var);
}

char	*single_quote(char *content)
{
	int		i;
	int		count;
	char	*var;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == '\'')
		{
			i++;
			continue ;
		}
		i++;
		count++;
	}
	var = gc_malloc(sizeof(char) * (count + 1));
	if (!var)
		return (NULL);
	var = stcopy(var, content, '\'');
	return (var);
}
