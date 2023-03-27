/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:30:06 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/27 10:27:43 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_menager(char *str, int id)
{
	long long	time;

	time = current_time();
	id++;
	pthread_mutex_lock(&handler()->write);
	if (!ft_strncmp(str, "FORK", 4))
		printf("%lld %d has taken a fork\n", time, id);
	else if (!ft_strncmp(str, "EAT", 3))
		printf("%lld %d is eating\n", time, id);
	else if (!ft_strncmp(str, "SLEEP", 5))
		printf("%lld %d is sleeping\n", time, id);
	else if (!ft_strncmp(str, "THINK", 5))
		printf("%lld %d is thinking\n", time, id);
	else if (!ft_strncmp(str, "DIED", 4))
		printf("%lld %d died\n", time, id);
	pthread_mutex_unlock(&handler()->write);
}

bool	cheak_death(void)
{
	bool	tog;

	pthread_mutex_lock(&handler()->death);
	tog = handler()->dead_philo;
	pthread_mutex_unlock(&handler()->death);
	return (tog);
}

void	*runtime(void *arg)
{
	t_philo	*self;

	self = arg;
	self->last_meal = current_time();
	self->num_of_times_ate = 0;
	if (self->id % 2 != 0)
	{
		print_menager("THINK", self->id);
		ft_sleep(handler()->time_to_eat);
	}
	while (self->num_of_times_ate < handler()->nbr_times_to_eat)
	{
		if (cheak_death() || dead(self))
			break ;
		if (handler()->n_threads > 1 && eat(self))
		{
			if (cheak_death())
				break ;
			phi_sleep(self);
		}
		if (cheak_death() || dead(self))
			break ;
		think(self);
	}
	return (NULL);
}
