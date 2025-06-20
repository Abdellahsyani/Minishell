/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:22:45 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 16:24:46 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_fd(t_env **env, char c, char next, int fd)
{
	char	*var;

	if (c == '$' && next == '?')
	{
		var = ft_get(env, "?");
		ft_putstr_fd(var, fd);
	}
	else if (c == '$' && next == '0')
		ft_putstr_fd("minishell", fd);
}

int	ft_expand_dolar(char *line, t_env **env, int *i, int fd)
{
	char	*var;
	char	*var1;
	int		len;

	var = NULL;
	var1 = NULL;
	if (!line)
		return (0);
	var = get_var1(&line[*i]);
	var1 = get_var(&line[*i], env, 1);
	ft_putstr_fd(var1, fd);
	len = ft_strlen(var);
	return (len);
}

void	helper_herdoc(char *line, int fd, t_env **env)
{
	int		i;
	int		len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '?' || line[i + 1] == '0'))
		{
			ft_write_fd(env, line[i], line[i + 1], fd);
			i += 2;
			continue ;
		}
		else if (line[i] == '$' && (ft_isalpha(line[i+1])))
		{
			len = ft_expand_dolar(line, env, &i, fd);
			i += len;
		}
		else
			write(fd, &line[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
