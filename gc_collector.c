/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:47 by asyani            #+#    #+#             */
/*   Updated: 2025/06/02 16:22:32 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static c_list	*head;

void	ft_free_gc(void)
{
	c_list			*tmp;

	tmp = head;
	while (tmp)
	{
		c_list *next = tmp->next;
		if(tmp->data)
			free(tmp->data); 
		free(tmp);
		tmp = next;
	}
	head = NULL;
}

void	*gc_malloc(size_t size)
{
	c_list	*node;
	c_list	*tmp;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	node = malloc(sizeof(t_list));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->data = ptr;
	node->next = NULL;
	if (head == NULL)
		head = node;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (ptr);
}
