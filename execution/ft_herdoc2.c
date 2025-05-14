/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:22:45 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/14 18:47:24 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_dollar(char *line, int fd)
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
            value = (ft_find(env, "$"));
            printf("%s\n", value);
            write(fd, value, ft_strlen(value));
            free(value);
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

int main(int ac, char **arg, char **env)
{
    t_env **envp;

    envp = get_env(env);
    
    helper_herdoc(arg[1], 1, *envp);
    write(1,"\n", 1);
    
    return 0;
}