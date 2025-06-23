/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:46 by asyani            #+#    #+#             */
/*   Updated: 2025/06/23 18:25:44 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H
# include "minishell.h"
# include <stddef.h>
# include <signal.h>

/* struct for gc_collector */

typedef struct j_list
{
	int             type;
 	void			*ptr;
 	struct j_list	*next;
}	c_list;

typedef struct s_gc
{
	c_list *head;
	struct s_env	**env;
}	t_gc;

extern t_gc *gc_global;

void	gc_free_all(void);
void	*gc_malloc(size_t size);
void	init_gc(void);
void	gc_free_one(void *ptr);

#endif
