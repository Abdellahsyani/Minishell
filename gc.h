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
# include <signal.h>
# include <stddef.h>

/* struct for gc_collector */

typedef struct j_list
{
	int				type;
	void			*ptr;
	struct j_list	*next;
}					t_llist;

typedef struct s_gc
{
	t_llist			*head;
	int				count_quote;
	struct s_env	**env;
}					t_gc;

extern t_gc			*g_global;

void				gc_free_all(void);
void				*gc_malloc(size_t size);
void				init_gc(void);
void				gc_free_one(void *ptr);

#endif
