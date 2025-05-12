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

int is_builtin(t_command *cmd)
{
    if (!ft_strcmp(cmd->arg[0], "echo") || !ft_strcmp(cmd->arg[0], "cd"))
        return (1);
    else if (!ft_strcmp(cmd->arg[0], "export") || !ft_strcmp(cmd->arg[0], "unset"))
        return (1);
    else if (!ft_strcmp(cmd->arg[0], "env") || !ft_strcmp(cmd->arg[0], "pwd"))
        return (1);
    else if (!ft_strcmp(cmd->arg[0], "exit"))
        return (1);
    return (0);
}
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
int ft_child_process(t_command *cmd)
{
    char    *path;

    path = find_path(cmd,cmd->env);
    if (execve(path, cmd->arg, cmd->env) == -1)
    {
        perror("Execve");
        free (path);
        return(1);
    }
    free (path);
    return (0);
}

int simple_cmd(t_command *cmd)
{
    int pid;
    int status;
    
    if (is_builtin(cmd))
        return (exec_builtin(cmd->arg[0],cmd->arg, cmd->env));
    else
    {
        pid = fork();
        if (pid < 0)
        {
            printf ("Error: fork failed.\n");
            return (1);
        }
        else if (pid == 0)
            return (ft_child_process(cmd));  
            
        else 
        {
            wait(&status);
            //cmd->status = ft_itoa(WEXITSTATUS(status));
            if (WEXITSTATUS(status) != EXIT_SUCCESS)
                return (1);
            return (0);
        }
    }
}

int main(int ac, char **arg, char **env)
{
    (void)ac;
    t_env **envp;
    
    envp = get_env(env);
    printf("%s\n", find_path(arg[1],envp));
    return (0);
    
}