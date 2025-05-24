/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:47 by asyani            #+#    #+#             */
/*   Updated: 2025/04/24 18:10:02 by asyani           ###   ########.fr       */
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
