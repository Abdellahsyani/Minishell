/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:03:42 by asyani            #+#    #+#             */
/*   Updated: 2025/04/28 17:04:09 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strlcpy(char *token, char *input, int len, int j)
{
	int	i;

	i = 0;
	token = malloc(sizeof(char) * len + 1);
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
