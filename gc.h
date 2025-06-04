/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:30:46 by asyani            #+#    #+#             */
/*   Updated: 2025/06/04 11:39:59 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

#include "minishell.h"

typedef enum e_gc_type
{
    e_dont_free,
    e_free_content,
    e_free_all,
} t_gc_type;

/* struct for gc_collector */
typedef struct j_list
{
	int             type;
 	void			*data;
 	struct j_list	*next;
}	c_list;

typedef struct s_gc
{
	c_list *gc_list;
}	t_gc;

extern t_gc *gc_global;

void	ft_free_gc(void);
int gc_type(int set, int value);
void	*gc_malloc(size_t size);

#endif
