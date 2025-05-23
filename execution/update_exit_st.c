/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_st.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:08:28 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/23 16:55:31 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_exit_status(t_env **env,int status)
{
	char *value;

	value = ft_itoa(status);
	set_new_env("?", value, env);
}

int wait_and_free(t_extra ptr)
{
	int status;
	int i;
	int new_status;

	i = 0;
	ft_free_gc();
	closingfds(ptr.pipline, ptr.size);
	while (i < ptr.size)
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
	}
	free(ptr.pid);
	return (new_status);
}
