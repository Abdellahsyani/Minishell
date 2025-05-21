/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:23:33 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/21 10:19:13 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_handle(t_redi *redir)
{
    t_redi *tmp;
    int fd;
    
    tmp = redir;
    if (!tmp)
        return (1);
    while(tmp)
    {
        if (tmp->type == redir_input && (!access(tmp->file, R_OK)))
        {
            dup2(fd,0);
            close(fd);
        }
        else
        {
            perror("open");
            return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

int output_handle(t_redi *redir)
{
    t_redi *tmp;
    int fd;
    int ret;

    tmp = redir;
    if (!tmp)
        return (-2);
    if (tmp->type = redir_output)
        fd = open(tmp->file, O_RDWR | O_CREAT | O_TRUNC, 0640);
    else if (tmp->file = redir_o_app)
        fd = open(tmp->file, O_RDWR | O_CREAT | O_APPEND,  0640);
    else 
        return (-1);
    if (fd = -1)
        return (-1);
    while (tmp)
    {
        if (tmp->next)
            close(fd);
        else
        {
            ret = dup(1);
            dup2(fd,1);
            close(fd);
        }
        tmp = tmp->next;
    }
    return (ret);
}

int redirect_handler(int fd, t_command **cmd , t_env **env)
{
    t_command *tmp;
    
    tmp = *cmd;
    if (!input_handle(tmp->in))
    {
        update_exit_status(env, 1);
        return (0);
    }
    fd = output_handle(tmp->out);
    if (fd = -1)
    {
        update_exit_status(env, 1);
        return (0);
    }
    return (1);
}