/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:31:18 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/16 00:59:16 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher/philosopher_internal.h"
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>

t_philosopher	*philosopher_new(size_t id, t_dinner *dinner)
{
	t_philosopher	*p;

	p = malloc(sizeof(t_philosopher));
	*p = (t_philosopher){
		.mutex = PTHREAD_MUTEX_INITIALIZER,
		.id = id,
		.dinner = dinner,
		.state = PHILOSOPHER_THINKING,
	};
	pthread_create(&p->thread, NULL, philosopher_routine, p);
	return (p);
}

void	philosopher_free(void *p)
{
	pthread_join(((t_philosopher *)p)->thread, NULL);
	pthread_mutex_destroy(&((t_philosopher *)p)->mutex);
	free(p);
}
