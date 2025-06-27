/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_st.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:08:28 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/27 11:04:03 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_exit_status(t_env **env, int status)
{
	char	*value;

	value = ft_itoa(status);
	set_new_env("?", value, env);
}

void	init_extra(t_extra *ptr, t_env **env)
{
	(void)env;
	if (!ptr)
		return ;
	ptr->i = 0;
	ptr->env = env;
	ptr->flag_sig = 0;
}

void	closingfds(int **tube, int pos)
{
	while (pos > 0)
	{
		close(tube[pos - 1][0]);
		close(tube[pos - 1][1]);
		pos--;
	}
}

int	ft_cmd_size(t_command **cmd)
{
	t_command	*tmp;
	int			count;

	count = 0;
	if (!cmd)
		return (0);
	tmp = *cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	wait_and_free(t_extra ptr)
{
	int	status;
	int	i;
	int	new_status;

	i = 0;
	closingfds(ptr.pipline, ptr.size);
	signal(SIGINT, SIG_IGN);
	while (i <= ptr.size)
	{
		waitpid(ptr.pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			new_status = WEXITSTATUS(status);
			update_exit_status(ptr.env, new_status);
		}
		else
		{
			write(1, "\n", 1);
			new_status = 128 + WTERMSIG(status);
			update_exit_status(ptr.env, new_status);
		}
		i++;
	}
	signal(SIGINT, handle_sig);
}
