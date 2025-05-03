/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:53:11 by abhimi            #+#    #+#             */
/*   Updated: 2025/04/26 11:03:43 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
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

int	ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
