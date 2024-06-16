/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:47:55 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/15 14:28:56 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <stdlib.h>

typedef struct s_table_seat
{
	void				*entity;
	struct s_table_seat	*left;
	struct s_table_seat	*right;
}						t_table_seat;

typedef void			(*t_table_delete_func)(void *e);

typedef struct s_table
{
	t_table_seat		*seats;
	size_t				size;
	t_table_delete_func	delete;
}						t_table;

void					table_init(t_table *t, t_table_delete_func delete);
void					table_destroy(t_table *t);
void					table_add(t_table *t, void *entity);

#endif
