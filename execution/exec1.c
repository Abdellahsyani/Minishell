/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:09 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/06 16:37:30 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_path(char *cmd, t_env **env)
{
    int i;
    t_env *cur;
    char **paths;
    char    *path;

    i = 0;
    cur = *env;
    while(ft_strncmp(cur->key,"PATH",4))
        cur = cur->next;
    paths = ft_split(cur->value, ':');
    while (paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        path = ft_strjoin(paths[i], cmd);
        if (!access(path, X_OK))
        {
            ft_free(paths);
            return (path);
        }
        free(paths[i]);
        free(path);
        i++;
    }
    return (NULL);
}

int simple_cmd(t_command *cmd)
{
    int pid;
    
    if (is_builtin(cmd->name))
        return (exec_builtin(cmd->name,cmd->arg, cmd->env));
    else
    {
        pid = fork();
        if (pid == 0)
        {
            return (ft_child_process(cmd));  
        }
        else 
            //??
    }
}

int main(int ac, char **arg, char **envp)
{
    (void)ac;
    
    printf("%s\n", find_path(arg[1],envp));
    return (0);
    
}