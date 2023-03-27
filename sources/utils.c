/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:53:30 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/27 11:43:48 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_handler	*handler(void)
{
	static t_handler	handler;

	return (&handler);
}

int	error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	current_time(void)
{
	return (get_time() - handler()->start_time);
}

void	ft_sleep(long long time)
{
	long long	f_time;

	f_time = get_time() + time;
	while (get_time() < f_time)
		usleep(1);
}
