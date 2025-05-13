/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:23:33 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/13 09:54:17 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_handle(t_redi *redir, int fd)
{
    t_redi *tmp;

    tmp = redir;

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
    return (1);
}

int output_handle(t_redi *redir)
{
    t_redi *tmp;
    int fd;
    int ret;

    tmp = redir;
    
    if (tmp->type = redir_output)
    {
        fd = open(tmp->file, O_RDWR | O_CREAT | O_TRUNC, 0640);
    }
    else if (tmp->file = redir_o_app)
        fd = open(tmp->file, O_RDWR | O_CREAT | O_APPEND,  0640);
    while (tmp)
    {
        if (!tmp->next)
        {
            dup2(fd, 1);
            close(fd);
            return (0);
        }
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

int redirect_handler(t_redi *redir)
{
    int fd;
    
    if (!input_handle(redir,fd))
    {
        return (0);
    }
    if (!output_handle(redir))
    {
        return (0);
    }
    return (1);
}