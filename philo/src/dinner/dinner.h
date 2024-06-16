/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:45:40 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/17 21:36:54 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DINNER_H
# define DINNER_H

# include "table.h"
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_dinner
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	log_lock;
	t_table			table;
	pthread_mutex_t	*forks;
	size_t			size;
	suseconds_t		start_time;
	suseconds_t		lifetime;
	suseconds_t		meal_duration;
	suseconds_t		sleep_duration;
	ssize_t			meals_needed;
	bool			ended;
}					t_dinner;

typedef enum e_dinner_error
{
	DINNER_SUCCESS = 0,
	DINNER_INVALID_ARGS,
}					t_dinner_error;

t_dinner_error		dinner_from_args(const char *args[], t_dinner *d);
void				dinner_run(t_dinner *d);
suseconds_t			dinner_elapsed_time(t_dinner *d);
bool				dinner_has_ended(t_dinner *d);

#endif
