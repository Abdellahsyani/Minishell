/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:57:42 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/19 13:45:21 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cmd_size(t_command **cmd)
{
    t_command *tmp;
    int count;
    if (!*cmd)
        return (0);
    tmp = *cmd;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return(count);
}
void exec_builtins(t_command **cmd, t_env **env)
{
    int fd;
    int status;
    t_command *tmp;

    tmp = *cmd;
    if (!redirect_handler(fd, cmd, env))
        return ;
    status = ft_exec_builtin(tmp->arg[0], tmp->arg, env);
    update_exit_status(env, status);
    if(fd == -2)
    {
        dup2(fd, 1);
        close(fd);
    }
}

int **allocate_tube(size)
{
    int **tube;
    int i;

    i = 0;
    tube = gc_malloc(size);
    if (!tube)
        return (0);
    while (i < size)
    {
        tube[i] = gc_malloc(2);
        if(!tube[i])
            return (0);
        i++;
    }
    return (tube);
} 
int set_pipes(int **tube, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        if(pipe(tube[i]) == -1)
            return (0); //need to close fds
        i++;
    }
    return (1);
}
int **built_pipline(t_command **cmd ,t_env **env, int size)
{
    t_command *tmp;
    int **tube;
    
    tmp  = *cmd;
    if (size = 0 && tmp->arg && is_builtin(tmp))
    {
        exec_builtins(cmd, env);
        return (NULL);
    }
    tube = allocate_tube(size);
    if(!tube || !set_pipes(tube, size))
    {
        ft_error("Error: pipe failed or allocation.\n");
        update_exit_status(env, 1);
        //need close fds;
        return (NULL);
    }
    return (tube);
}


void    handle_child(t_command *cmd, t_env **env, t_extra ptr)
{
    if (!cmd->in)
    {
        if (ptr.i != ptr.size)
            dup2(ptr.pipline[ptr.i - 1][0], 0);
    }
   input_handle(cmd->in);
   if(!cmd->out)
   {
        if (ptr.i != ptr.size)
        {
            dup2(ptr.pipline[ptr.i][1], 1);
        }
   }
   output_handle(cmd->out);
   
}

void ft_exec(t_command **cmd, t_env **env)
{
    t_extra ptr;
    t_command *tmp;
    
    tmp = *cmd;
    ptr.size = ft_cmd_size(cmd) - 1;
    ptr.i = 0;
    ptr.pipline = built_pipline(cmd, env, ptr.size);
    if (!ptr.pipline)
        return ;
    ptr.env = env;
    ptr.pid = gc_malloc(ptr.size);
    ft_herdoc(cmd, &ptr);
    while (ptr.i < ptr.size)
    {
        ptr.pid[ptr.i] = fork();
        if (!ptr.pid[ptr.i])
            handle_child(tmp,env,ptr);
        ptr.i++;
        tmp = tmp->next;
    }
    wait_and_free();
}