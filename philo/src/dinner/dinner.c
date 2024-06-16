/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/17 21:10:36 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner/dinner_internal.h"
#include "philosopher/philosopher.h"
#include "utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>

static void		dinner_init(t_dinner *d);
static void		dinner_destroy(t_dinner *d);

t_dinner_error	dinner_from_args(const char *args[], t_dinner *d)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (!is_positive_number(args[i]))
			return (DINNER_INVALID_ARGS);
		i++;
	}
	if (i < 4 || i > 5)
		return (DINNER_INVALID_ARGS);
	*d = (t_dinner){
		.size = utils_atol(args[0]),
		.lifetime = utils_atol(args[1]) * 1000,
		.meal_duration = utils_atol(args[2]) * 1000,
		.sleep_duration = utils_atol(args[3]) * 1000,
		.meals_needed = -1,
	};
	if (args[4] != NULL)
		d->meals_needed = utils_atol(args[4]);
	return (DINNER_SUCCESS);
}

void	dinner_run(t_dinner *d)
{
	dinner_init(d);
	d->start_time = utils_get_time_us();
	while (d->table.size < d->size)
		table_add(&d->table, philosopher_new(d->table.size + 1, d));
	dinner_watch(d);
	dinner_destroy(d);
}

suseconds_t	dinner_elapsed_time(t_dinner *d)
{
	return (utils_get_time_us() - d->start_time);
}

static void	dinner_init(t_dinner *d)
{
	size_t	i;

	d->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	d->log_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table_init(&d->table, philosopher_free);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->size);
	i = 0;
	while (i < d->size)
	{
		d->forks[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
	d->ended = false;
}

static void	dinner_destroy(t_dinner *d)
{
	size_t	i;

	table_destroy(&d->table);
	i = 0;
	while (i < d->size)
	{
		pthread_mutex_destroy(&d->forks[i]);
		i++;
	}
	free(d->forks);
	pthread_mutex_destroy(&d->log_lock);
	pthread_mutex_destroy(&d->mutex);
}
