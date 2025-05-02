/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:51:44 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/02 09:25:29 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(t_env *env)
{
    t_env *tmp;
    
    tmp = env;
    if (!tmp)
        return ;
    while(tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
}
