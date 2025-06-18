/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:51:41 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/17 14:55:22 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*p;
	size_t		i;
	size_t		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !*s1)
		return (ft_strdup(s2));
	if (!s2 || !*s2)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	p = gc_malloc(sizeof(char) * (ft_strlen(s1) +ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	while (i < ft_strlen(s1))
		p[j++] = s1[i++];
	i = 0;
	while (i < ft_strlen(s2))
		p[j++] = s2[i++];
	p[j] = '\0';
	return (p);
}
