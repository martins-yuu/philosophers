/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:08:09 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/18 19:08:10 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher/philosopher_internal.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void	do_eat(t_philosopher *p);
static void	do_sleep(t_philosopher *p);
static void	do_think(t_philosopher *p);
static void	take_forks(t_philosopher *p);

void	*philosopher_routine(void *arg)
{
	t_philosopher	*p;

	p = arg;
	p->left_fork = &p->dinner->forks[p->id - 1];
	if (p->dinner->size == 1)
	{
		philosopher_set_state(p, PHILOSOPHER_TOOK_FORK);
		return (NULL);
	}
	p->right_fork = &p->dinner->forks[p->id % p->dinner->size];
	while (!dinner_has_ended(p->dinner))
	{
		do_eat(p);
		do_sleep(p);
		do_think(p);
	}
	return (NULL);
}

static void	do_eat(t_philosopher *p)
{
	take_forks(p);
	philosopher_set_state(p, PHILOSOPHER_EATING);
	pthread_mutex_lock(&p->mutex);
	p->last_meal = dinner_elapsed_time(p->dinner);
	p->meal_count++;
	pthread_mutex_unlock(&p->mutex);
	usleep(p->dinner->meal_duration);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static void	do_sleep(t_philosopher *p)
{
	philosopher_set_state(p, PHILOSOPHER_SLEEPING);
	usleep(p->dinner->sleep_duration);
}

static void	do_think(t_philosopher *p)
{
	philosopher_set_state(p, PHILOSOPHER_THINKING);
}

static void	take_forks(t_philosopher *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->left_fork);
		philosopher_set_state(p, PHILOSOPHER_TOOK_FORK);
		pthread_mutex_lock(p->right_fork);
		philosopher_set_state(p, PHILOSOPHER_TOOK_FORK);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		philosopher_set_state(p, PHILOSOPHER_TOOK_FORK);
		pthread_mutex_lock(p->left_fork);
		philosopher_set_state(p, PHILOSOPHER_TOOK_FORK);
	}
}
