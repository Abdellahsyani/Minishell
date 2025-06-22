/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:47 by asyani            #+#    #+#             */
/*   Updated: 2025/06/22 16:36:32 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	*gc_global = NULL;

void	init_gc(void)
{
	gc_global = malloc(sizeof(t_gc));
	if (!gc_global)
		return ;
	gc_global->head = NULL;
}

void	*gc_malloc(size_t size)
{
	void		*ptr;
	c_list	*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	node = malloc(sizeof(c_list));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = gc_global->head;
	gc_global->head = node;
	return (ptr);
}

void	gc_free_one(void *ptr)
{
	c_list *curr;
	c_list *prev;

	prev = NULL;
	curr = gc_global->head;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				gc_global->head = curr->next;
			free(curr->ptr);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_free_all(void)
{
	c_list	*next;
	c_list	*curr;

	curr = gc_global->head;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	free(gc_global);
	gc_global = NULL;
}
