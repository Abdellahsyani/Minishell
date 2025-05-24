/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:22:45 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/15 01:29:01 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_dollar(char *line, int fd)
{
	(void)line;
	int pid;
	char *s;
	pid = getpid();
	s = ft_itoa(pid);
	write(fd, s, ft_strlen(s));
	free(s);
}

void helper_herdoc(char *line, int fd, t_env **env)
{
	int i = 0;
	t_env *envp;

	while (line[i])
	{
		if (line[i] ==  '$' && line[i + 1] == '?')
		{
			envp = ft_find(*env, "?");
			printf("%s\n", envp->value);
			write(fd, envp->value, ft_strlen(envp->value));
			free(envp);
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			ft_dollar(line, fd);
			i += 2;
		}

		else if (line[i] == '$' && line[i + 1] == '0')
		{
			write(fd, "minishell", 9);
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1] == '\0')
			write(fd, "$1", 1);
		else
			write(fd, &line[i], 1);
		i++;
	}
}

// int main(int ac, char **arg, char **env)
// {
//     t_env **envp;

//     envp = get_env(env);

//     helper_herdoc(arg[1], 1, *envp);
//     write(1,"\n", 1);

//     return 0;
// }
