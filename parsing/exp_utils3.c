/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:47 by asyani            #+#    #+#             */
/*   Updated: 2025/06/21 18:48:36 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_space(char *str, char *result, int *i, int *j)
{
	int	k;

	k = *i;
	while (str[k] && (str[k] == ' ' || str[k] == '\t'))
		k++;
	if (str[k])
		result[(*j)++] = ' ';
}

void	failure_alloc(t_command *cmd, char *ex)
{
	cmd->argv = gc_malloc(sizeof(char *) * 2);
	if (!cmd->argv)
		return ;
	if (!ex)
		cmd->argv[0] = ft_strdup("$");
	else
		cmd->argv[0] = ft_strdup(ex);
	cmd->argv[1] = NULL;
}

char	*ft_strjoins(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	return (s1);
}

static char	*when_quote(char *var, char *quote, int i)
{
	char	*copy;

	copy = NULL;
	copy = ft_strlcpy(copy, var, i, 0);
	copy = ft_strjoin(copy, quote);
	return (copy);
}

char	*copy_var(char *content, t_env **env, int i)
{
	int		len;
	char	*var;
	char	*quote;

	var = NULL;
	quote = NULL;
	len = ft_strlen(content);
	var = ft_strlcpy(var, content, len, 0);
	while (var[i])
	{
		if (var[i] == '"')
		{
			quote = double_quote(&var[i], env);
			break ;
		}
		if (var[i] == '\'')
		{
			quote = single_quote(&var[i]);
			break ;
		}
		i++;
	}
	if (quote)
		return (when_quote(var, quote, i));
	return (var);
}
