/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:01:58 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/28 19:56:22 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sig(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_child_sig(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	gc_free_all();
	rl_clear_history();
	exit(130);
}

char	*rm_newline(char *limit)
{
	int		l;
	int		i;
	char	*str;

	i = 0;
	if (!*limit)
		return (ft_strdup(""));
	l = ft_strlen(limit);
	str = gc_malloc(sizeof(char) * l);
	while (limit[i] != '\n')
	{
		str[i] = limit[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	check_null_path(t_env **env, char *str)
{
	if (access(str, F_OK) && slash(str))
		ft_error(env, str, " : No such file or directory\n", 127);
	else if (str[0] == '.' && str[1])
		ft_error(env, str, ": Permission denied\n", 126);
	else
		ft_error(env, str, ": command not found\n", 127);
}
