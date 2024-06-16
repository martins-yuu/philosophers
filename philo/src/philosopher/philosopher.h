/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:29:59 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/18 02:40:36 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "dinner/dinner.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_philosopher	t_philosopher;

typedef enum e_philosopher_state
{
	PHILOSOPHER_TOOK_FORK,
	PHILOSOPHER_EATING,
	PHILOSOPHER_SLEEPING,
	PHILOSOPHER_THINKING,
	PHILOSOPHER_DEAD,
}								t_philosopher_state;

t_philosopher					*philosopher_new(size_t id, t_dinner *dinner);
void							philosopher_free(void *p);
void							philosopher_set_state(t_philosopher *p,
									t_philosopher_state ps);
bool							philosopher_has_starved(t_philosopher *p);
bool							philosopher_is_sated(t_philosopher *p);

#endif
