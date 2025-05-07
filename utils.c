/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:53:11 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/06 15:08:50 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
   while(s1[i] || s2[i])
   {
        if(s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
   }
   return (0);
}

int ft_strncmp(char *s1, char *s2, int l)
{
    int i;
    
    i = 0;
    while (s1[i] && i != l)
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (0);
}