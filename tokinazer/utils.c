/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:53:11 by abhimi            #+#    #+#             */
/*   Updated: 2025/05/28 14:25:38 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_strlcpy(char *token, char *input, int len, int j)
{
	int	i;

 	i = 0;
 	token = gc_malloc(sizeof(char) * len + 1);
 	if (!token)
 		return (NULL);
 	while (i < len)
 	{
 		token[i] = input[j + i];
 		i++;
 	}
 	token[i] = '\0';
 	return (token);
}

int	is_operator(char op)
{
	if (op == '>' || op == '<' || op == '|')
		return (1);
	return (0);
}

void ft_sort(t_env **env)
{
	t_env *tmp;
	t_env *cur;
	int l;
	int i = 0;
	int j;
	
	tmp = *env;
	l = 0;
	while (tmp)
	{
		l++;
		tmp = tmp->next;
	}
	tmp = *env;
	cur  = *env;
	while (i < l)
	{
		j = 0;
		while (j < l - i - 1)
		{
			if(cur->key[j] > cur->next->key[j + 1])
			{
				tmp = cur->next;
				cur->next = cur;
				cur = tmp ;
			}
			j++;
			cur = cur->next;
		}
		i++;
	}
}