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

#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

static t_list	*head;

void	ft_free_gc(void)
{
	t_list			*tmp;

	tmp = head;
	while (tmp)
	{
		t_list *next = tmp->next;
		free(tmp->data); 
		free(tmp);
		tmp = next;
	}
	head = NULL;
}

void	*gc_malloc(size_t size)
{
	t_list	*node;
	t_list	*tmp;
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

int main()
{
	int *str;

	str = gc_malloc(sizeof(char) * 11);
	int i = 0;
	int count = 100;
	while (i < 10)
	{
		str[i] = count;
		printf("%d ", str[i]);
		count++;
		i++;
	}
	ft_free_gc();
	return 0;
}
