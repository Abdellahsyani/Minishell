/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:22:45 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/16 12:52:17 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_dollar(char *line, int fd, t_env **env)
{
	(void)line;
	char *s;
	
	s = ft_itoa((*env)->pid);
	write(fd, s, ft_strlen(s));
	free(s);
}

void helper_herdoc(char *line, int fd, t_env **env)
{
	int i = 0;
	t_env *envp;
	char *var = NULL;
	char *var1 = NULL;

	while (line[i])
	{
		if (line[i] ==  '$' && line[i + 1] == '?')
		{
			envp = ft_find(*env, "?");
			// printf("%s\n", envp->value);
			write(fd, envp->value, ft_strlen(envp->value));
			i += 2;
			continue;
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			ft_dollar(line, fd, env);
			i += 2;
			continue;
		}

		else if (line[i] == '$' && line[i + 1] == '0')
		{
			write(fd, "minishell", 9);
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1] == '\0')
			write(fd, "$1", 1);
		else if (line[i] == '$' && (ft_isalpha(line[i+1])))
		{
			var = get_var1(&line[i]);
 			var1 = get_var(&line[i], env);
			write(fd, var1, ft_strlen(var1));
			int len = ft_strlen(var);
			i += len;
			// write(fd, &line[i], 1);
		}
		else
			write(fd, &line[i], 1);
		i++;
	}
	write(fd,"\n", 1);
}

// int main(int ac, char **arg, char **env)
// {
//     t_env **envp;

//     envp = get_env(env);

//     helper_herdoc(arg[1], 1, *envp);
//     write(1,"\n", 1);

//     return 0;
// }
