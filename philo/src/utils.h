/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:25:50 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/15 15:55:41 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <sys/time.h>

bool		utils_isdigit(char c);
bool		utils_isspace(char c);
long		utils_atol(const char *nptr);
bool		is_positive_number(const char *str);
suseconds_t	utils_get_time_us(void);

#endif
