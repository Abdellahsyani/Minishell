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

t_gc	*g_global = NULL;

void	init_gc(void)
{
	g_global = malloc(sizeof(t_gc));
	if (!g_global)
		return ;
	g_global->head = NULL;
}

void	*gc_malloc(size_t size)
{
	void	*ptr;
	t_llist	*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	node = malloc(sizeof(t_llist));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = g_global->head;
	g_global->head = node;
	return (ptr);
}

void	gc_free_one(void *ptr)
{
	t_llist	*curr;
	t_llist	*prev;

	prev = NULL;
	curr = g_global->head;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				g_global->head = curr->next;
			free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_free_all(void)
{
	t_llist	*next;
	t_llist	*curr;

	curr = g_global->head;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	free(g_global);
	g_global = NULL;
}
