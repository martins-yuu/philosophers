/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:29:05 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/18 19:16:01 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher/philosopher_internal.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static void	philosopher_log(t_philosopher *p);

void	philosopher_set_state(t_philosopher *p, t_philosopher_state ps)
{
	pthread_mutex_lock(&p->mutex);
	p->state = ps;
	philosopher_log(p);
	pthread_mutex_unlock(&p->mutex);
}

bool	philosopher_has_starved(t_philosopher *p)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&p->mutex);
	if (p->last_meal + p->dinner->lifetime < dinner_elapsed_time(p->dinner))
		ret = true;
	pthread_mutex_unlock(&p->mutex);
	return (ret);
}

bool	philosopher_is_sated(t_philosopher *p)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&p->mutex);
	if ((ssize_t)p->meal_count >= p->dinner->meals_needed)
		ret = true;
	pthread_mutex_unlock(&p->mutex);
	return (ret);
}

static void	philosopher_log(t_philosopher *p)
{
	static const char	*state_str[] = {
	[PHILOSOPHER_TOOK_FORK] = "has taken a fork",
	[PHILOSOPHER_EATING] = "is eating",
	[PHILOSOPHER_SLEEPING] = "is sleeping",
	[PHILOSOPHER_THINKING] = "is thinking",
	[PHILOSOPHER_DEAD] = "died",
	};

	if (dinner_has_ended(p->dinner))
		return ;
	pthread_mutex_lock(&p->dinner->log_lock);
	printf("%ld %zd %s\n", dinner_elapsed_time(p->dinner) / 1000, p->id,
		state_str[p->state]);
	pthread_mutex_unlock(&p->dinner->log_lock);
}
