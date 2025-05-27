/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:23:33 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/27 13:48:23 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_handle(t_redi *redir)
{
	t_redi *tmp;
	
	tmp = redir;
	if (!tmp) 
		return (1);
	while(tmp)
	{
		if (tmp->type == redir_input && access(tmp->file, R_OK) == -1)
		{
			perror("ERROR");
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
	while (tmp)
	{
		if ((tmp->type == redir_output || tmp->type == redir_o_app)	&& pass_out(tmp, &fd))
		{
			if (tmp->next)
				close(fd);
			else
			{
				ret = dup(1);
				dup2(fd,1);
				close(fd);
			}
		}
			tmp = tmp->next;
	}
	return (ret);
}

int redirect_handler(int *fd, t_command **cmd , t_env **env)
{
	t_command *tmp;
	(void)env;

	tmp = *cmd;
	if (!input_handle(tmp->in))
	{
		update_exit_status(env, 1);
		return (0);
	}
	*fd = output_handle(tmp->out);
	if (*fd == -1)
	{
		update_exit_status(env, 1);
		return (0);
	}
	return (1);
}
