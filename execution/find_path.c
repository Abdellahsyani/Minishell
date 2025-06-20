/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:09 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 11:09:07 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *cmd, t_env **env)
{
	int		i;
	t_env	*cur;
	char	**paths;
	char	*ppth;
	char	*path;

	i = -1;
	if (!access(cmd, X_OK))
		return (cmd);
	cur = *env;
	while (ft_strncmp(cur->key, "PATH", 4))
		cur = cur->next;
	paths = ft_split(cur->value, ':');
	while (paths[++i])
	{
		ppth = ft_strjoin(paths[i], "/");
		path = ft_strjoin(ppth, cmd);
		gc_free_one(ppth);
		if (!access(path, X_OK))
		{
			gc_free_one(paths[i]);
			return (path);
		}
	}
	return (NULL);
}
