/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:45:51 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/16 19:24:36 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_INTERNAL_H
# define PHILOSOPHER_INTERNAL_H

# include "philosopher/philosopher.h"
# include <pthread.h>
# include <stddef.h>

struct					s_philosopher
{
	pthread_t			thread;
	pthread_mutex_t		mutex;
	size_t				id;
	t_philosopher_state	state;
	t_dinner			*dinner;
	suseconds_t			last_meal;
	size_t				meal_count;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
};

void					*philosopher_routine(void *arg);

#endif
