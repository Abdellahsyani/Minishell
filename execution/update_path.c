/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:07:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/18 09:57:17 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*ft_strdup1(const char *s1)
{
	char	*p;
	int		i;
	if (!s1)
		return (NULL);
	p = gc_malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
void update_path(char *arg, t_env **env)
{
    t_env *tmp;
    char *new_value;
    char *value;
    char *str;
    int l;

    tmp = ft_find(*env, "_");
    value = ft_strdup(tmp->value);
    l = ft_strlen(value);
    while (l > 0)
    {
        if (value[l] == '/' && value[l - 1] != '.')
        {
            str = ft_substr(value, 0, l + 1);
            break ;
        }
        l--;
    }
    new_value = ft_strjoin(str, arg);
    if (!new_value)
        return ;
    set_new_env("_", new_value, env);
}


