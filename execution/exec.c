/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:57:42 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/24 11:57:57 by abhimi           ###   ########.fr       */
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
    if (!redirect_handler(&fd, cmd, env))
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
        {
            closingfds(tube, i);
            return (0);
        }
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
        exit(0) ;
    }
    tube = allocate_tube(size);
    if(!tube || !set_pipes(tube, size))
    {
        ft_error("Error: pipe failed or allocation.\n");
        update_exit_status(env, 1);
        //closingfds(tube, size);
        return (NULL);
    }
    return (tube);
}

void    closingfds(int **tube, int pos)
{
    while (pos > 0)
    {
        close(tube[pos - 1][0]);
        close(tube[pos - 1][1]);
        free(tube[pos - 1]);
        pos--;
    }
    free(tube);
}

int pass_out(t_redi *tmp ,int *fd)
{
    if (tmp->type == redir_output)
        *fd = open(tmp->file, O_RDWR | O_CREAT | O_TRUNC, 0640);
    else if (tmp->type == redir_o_app)
        *fd = open(tmp->file, O_RDWR | O_CREAT | O_APPEND, 0640);
    if (*fd == -1)
    {
        perror("open failed");
        return 0;
    }
    return (1);
}

void output_handle1(t_redi *tmp, t_extra ptr)
{
    int fd;
    if(!tmp)
   {
        if (ptr.i != ptr.size)
        {
            dup2(ptr.pipline[ptr.i][1], 1);
        }
   }
   while (tmp)
   {
        if (tmp->type == redir_input && tmp->type == redir_o_app && pass_out(tmp, &fd))
        {
            dup2(fd, 1);
            close(fd);   
        }
        tmp = tmp->next; 
   }
}

void pass_in(t_redi *tmp, int fd)
{
    if (fd  == -3)
        fd = open(tmp->file, O_RDONLY);
    if (fd  == -1)
    {
        perror("open failed");
        return ;
    }
    dup2(fd, 0);
    close(fd);
}
void input_handle1(t_redi *in, t_extra ptr, int fd)
{
    if (!in)
    {
        if (ptr.i != 0)
            dup2(ptr.pipline[ptr.i - 1][0], 0);
        return ;
    }
    while (in)
    {
        if (in->type ==  redir_input)
            pass_in(in, -3);
        else if (in->type == d_herdoc && !in->next)
            pass_in(in, fd);
        in = in->next;
    }
}
void exec_cmd(t_command *cmd, char *path,  t_env **env)
{
    int status;
    char    **envp;
    
    envp = chr_envirment(env);
    if (is_builtin(cmd->arg[0]))
    {
        status = ft_exec_builtin(cmd->arg[0], cmd->arg, env);
        update_exit_status(env, status);
        return ;
    }
    else
    {
        if (execve(path, cmd->arg, envp) == -1)
        {
            perror("execve failed.");
            return ;
        }
    }
}
void    handle_child(t_command *cmd, t_env **env, t_extra ptr)
{
    char *path;

    path = find_path(cmd, env);
    input_handle1(cmd->in,ptr, cmd->fd);
    output_handle1(cmd->out, ptr);
    if (path)
        exec_cmd(cmd, path,ptr.env);
    closingfds(ptr.pipline, ptr.i);
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