/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:07:16 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/28 11:33:06 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_path(char *arg, t_env **env)
{
    t_env *tmp;
    char *value;
    char *str;
    char *new_value;
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
    free(str);
    free(value);
}


