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
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len
				- 1] == '\n'))
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
