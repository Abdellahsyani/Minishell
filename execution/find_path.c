/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:09 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/12 11:54:19 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *find_path(char *cmd, t_env **env)
{
    int i;
    t_env   *cur;
    char    **paths;
    char    *ppth;
    char    *path;

    i = 0;
    if (!access(cmd, X_OK))
        return (cmd);
    cur = *env;
    while(ft_strncmp(cur->key,"PATH",4))
        cur = cur->next;
    paths = ft_split(cur->value, ':');
    while (paths[i])
    {
        ppth = ft_strjoin(paths[i], "/");
        path = ft_strjoin(ppth, cmd);
        free(ppth);
        if (!access(path, X_OK))
            return (path);
        free(paths[i]);
        free(path);
        i++;
    }
    return (NULL);
}
