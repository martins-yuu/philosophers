/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:27:43 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/15 15:55:35 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <sys/time.h>

bool	utils_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	utils_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

long	utils_atol(const char *nptr)
{
	long	res;
	size_t	i;
	int		sign;

	i = 0;
	while (utils_isspace(nptr[i]))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	res = 0;
	while (utils_isdigit(nptr[i]))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

bool	is_positive_number(const char *str)
{
	size_t	i;

	if (!str)
		return (false);
	i = 0;
	if (str[i] == '-')
		return (false);
	if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i] != '\0')
	{
		if (!utils_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

suseconds_t	utils_get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
}
