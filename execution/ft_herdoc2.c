/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:22:45 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/14 16:49:19 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_dollar(char *line, int fd, int *i)
{
    int pid;
    char *s;
    pid = getpid();
    s = ft_itoa(pid);
        write(fd, s, ft_strlen(s));
    free(s);
}

void helper_herdoc(char *line, int fd, t_env *env)
{
    int i;
    char *value;

    while (line[i])
    {
        if (line[i] ==  '$' && line[i + 1] == '?')
        {
            value = ft_find(env, "$");
            write(fd, value, ft_strlen(value));
            free(value);
            i += 2;
        }
        else if (line[i] == '$' && line[i + 1] == '$')
        {
            ft_dollar(line, fd , i);
            i += 2;
        }
        else if (line[i] == '$')
            write(fd, "$", 1);
        else
            write(fd, &line[i], 1);
        i++;
    }
}