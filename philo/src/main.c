/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/18 19:15:38 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner/dinner.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_dinner		d;
	t_dinner_error	err;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s "
			"<number_of_philosophers> "
			"<time_to_die> "
			"<time_to_eat> "
			"<time_to_sleep> "
			"[number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (EXIT_FAILURE);
	}
	err = dinner_from_args((const char **)argv + 1, &d);
	if (err)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	dinner_run(&d);
	return (EXIT_SUCCESS);
}
