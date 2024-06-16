/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:10 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/16 03:53:12 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"
#include <stdlib.h>

void	table_init(t_table *t, t_table_delete_func delete)
{
	*t = (t_table){
		.seats = NULL,
		.size = 0,
		.delete = delete,
	};
}

void	table_destroy(t_table *t)
{
	t_table_seat	*seat;
	t_table_seat	*next;

	seat = t->seats;
	while (t->size-- > 0)
	{
		next = seat->right;
		t->delete (seat->entity);
		free(seat);
		seat = next;
	}
	t->seats = NULL;
}

void	table_add(t_table *t, void *entity)
{
	t_table_seat	*seat;

	seat = malloc(sizeof(t_table_seat));
	seat->entity = entity;
	if (t->seats == NULL)
	{
		t->seats = seat;
		t->seats->left = seat;
		t->seats->right = seat;
	}
	else
	{
		seat->left = t->seats->left;
		seat->right = t->seats;
		t->seats->left->right = seat;
		t->seats->left = seat;
	}
	t->size++;
}
