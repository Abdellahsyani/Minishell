/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_st.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:08:28 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/05 10:16:45 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_exit_status(t_env **env,int status)
{
	char *value;

	value = ft_itoa(status);
	set_new_env("?", value, env);
	free(value);
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
int ft_cmd_size(t_command **cmd)
{
	t_command *tmp;
	int count;
	
	count = 0;
	if (!cmd)
		return (0);
	tmp = *cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return(count);
}
void ft_free(char **p)
{
	int i;
	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}
void wait_and_free(t_extra ptr)
{
	int status;
	int i;
	int new_status;

	i = 0;
	ft_free(ptr.envp);
	closingfds(ptr.pipline, ptr.size);
	while (i <= ptr.size)
	{
		waitpid(ptr.pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			new_status =  WEXITSTATUS(status);
			update_exit_status(ptr.env,new_status);
		}
		else
		{
			new_status = 128 + WEXITSTATUS(status);
			update_exit_status(ptr.env, new_status);
		}
		i++;
	}
}
