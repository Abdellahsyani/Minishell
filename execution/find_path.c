/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:09 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/20 17:39:03 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_regular_executable(const char *path)
{
	struct stat	sb;

	if (access(path, X_OK) != 0)
		return (0);
	if (stat(path, &sb) != 0)
		return (0);
	return (S_ISREG(sb.st_mode));
}

char	*find_path(char *cmd, t_env **env)
{
	int		i;
	t_env	*cur;
	char	**paths;
	char	*ppth;
	char	*path;

	i = -1;
	if (is_regular_executable(cmd))
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
