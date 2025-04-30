/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:51:44 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/30 15:01:49 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(s_env *env)
{
    s_env *tmp;
    
    tmp = env;
    if (!tmp)
        return ;
    while(tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
}
