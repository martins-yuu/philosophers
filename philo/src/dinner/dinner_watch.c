/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_watch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:07:43 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/18 19:07:44 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner/dinner.h"
#include "philosopher/philosopher.h"
#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

static bool	check_should_end(t_dinner *d);

bool	dinner_has_ended(t_dinner *d)
{
	bool	ret;

	pthread_mutex_lock(&d->mutex);
	ret = d->ended;
	pthread_mutex_unlock(&d->mutex);
	return (ret);
}

void	dinner_watch(t_dinner *d)
{
	if (check_should_end(d))
	{
		pthread_mutex_lock(&d->mutex);
		d->ended = true;
		pthread_mutex_unlock(&d->mutex);
	}
}

static bool	check_should_end(t_dinner *d)
{
	size_t			sated_count;
	t_table_seat	*seat;
	t_philosopher	*p;

	sated_count = 0;
	seat = d->table.seats;
	while (true)
	{
		p = seat->entity;
		if (philosopher_has_starved(p))
		{
			philosopher_set_state(p, PHILOSOPHER_DEAD);
			return (true);
		}
		if (philosopher_is_sated(p))
			sated_count++;
		else
			sated_count = 0;
		if (d->meals_needed != -1 && sated_count == d->table.size)
			return (true);
		seat = seat->right;
		usleep(1000);
	}
	return (false);
}
