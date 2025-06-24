/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:23:33 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/24 17:30:41 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pass_out(t_redi *tmp, int *fd)
{
	if (tmp->type == redir_output && tmp->file)
		*fd = open(tmp->file, O_RDWR | O_CREAT | O_TRUNC, 0640);
	else if (tmp->type == redir_o_app && tmp->file)
		*fd = open(tmp->file, O_RDWR | O_CREAT | O_APPEND, 0640);
	else
		return (-1);
	if (*fd == -1)
	{
		perror("open failed");
		return (0);
	}
	return (1);
}

int	input_handle(t_redi *redir)
{
	t_redi	*tmp;

	tmp = redir;
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (tmp->type == redir_input && access(tmp->file, R_OK) == -1)
		{
			perror(tmp->file);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	output_handle(t_redi *redir)
{
	int	fd;
	int	redout;

	if (!redir)
		return (-2);
	while (redir)
	{
		if ((redir->type == redir_output || redir->type == redir_o_app)
			&& pass_out(redir, &fd))
		{
			if (redir->next)
				close(fd);
			else
			{
				redout = dup(1);
				dup2(fd, 1);
				close(fd);
			}
		}
		else
			return (-1);
		redir = redir->next;
	}
	return (redout);
}

int	redirect_handler(int *fd, t_command **cmd, t_env **env)
{
	t_command	*tmp;

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
