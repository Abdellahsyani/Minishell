/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:33:19 by asyani            #+#    #+#             */
/*   Updated: 2025/06/28 10:36:32 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checks_token(const char *str)
{
	int		i;
	int		found_single;
	int		found_double;
	char	in_quote;

	i = 0;
	found_single = 0;
	found_double = 0;
	in_quote = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '"' || str[i] == '\''))
		{
			in_quote = str[i];
			if (in_quote == '"')
				found_double = 1;
			else
				found_single = 1;
		}
		else if (in_quote && str[i] == in_quote)
			in_quote = 0;
		i++;
	}
	return (found_single && found_double);
}

int	rem_quotes(char *var, char *content, int *i, int *j)
{
	char	del;

	if (content[*i] != '"' && content[*i] != '\'')
		return (0);
	del = content[(*i)++];
	if (del == '"')
		g_global->count_double += 1;
	else
		g_global->count_single += 1;
	while (content[*i])
	{
		if (content[*i] == del)
		{
			if (del == '"')
				g_global->count_double += 1;
			else
				g_global->count_single += 1;
			(*i)++;
			break ;
		}
		var[(*j)++] = content[(*i)++];
	}
	return (1);
}

int	when_var(t_command *cmd, t_env **env, int *j, int *i)
{
	char	*arg;

	arg = NULL;
	arg = get_var(cmd->argv_t[(*i)], env, 1);
	if (*arg)
	{
		cmd->argv[*j] = ft_strdup(arg);
		return (1);
	}
	return (0);
}

char	*trim_whitespace(char *str)
{
	int		len;
	char	*p;
	char	*str1;

	str1 = str;
	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n'))
		str[--len] = '\0';
	p = ft_strdup(str);
	free(str1);
	return (p);
}

void	clean_all(t_env **env, int n, int flag)
{
	(void)env;
	gc_free_all();
	env = NULL;
	rl_clear_history();
	if (flag == 1)
		write(1, "exit\n", 5);
	exit(n);
}
