/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:20:36 by abhimi            #+#    #+#             */
/*   Updated: 2025/06/18 09:53:39 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenum(int n)
{
	int	l;

	l = 0;
	if (n <= 0)
		l = 1;
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*p;
	int				i;
	int				len;

	len = ft_lenum(n);
	i = len - 1;
	p = gc_malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (i >= 0)
	{
		p[i] = (nb % 10) + '0';
		nb /= 10;
		if (i == 0 && n < 0)
			p[i] = '-';
		i--;
	}
	return (p);
}
