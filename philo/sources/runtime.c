/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:30:06 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/29 19:08:30 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead(t_philo *self)
{
	if (current_time() - self->last_meal >= handler()->time_to_die)
	{
		print_menager("DIED", self->id);
		handler()->dead_philo = true;
		return (true);
	}
	else
		return (false);
}

void	print_menager(char *str, int id)
{
	long long	time;

	id++;
	pthread_mutex_lock(&handler()->write);
	time = current_time();
	if (!ft_strncmp(str, "DIED", 4))
		printf("%lld %d died\n", time, id);
	else if (check_death(&handler()->philos[id - 1]))
	{
		pthread_mutex_unlock(&handler()->write);
		return ;
	}
	if (!ft_strncmp(str, "FORK", 4))
		printf("%lld %d has taken a fork\n", time, id);
	else if (!ft_strncmp(str, "EAT", 3))
		printf("%lld %d is eating\n", time, id);
	else if (!ft_strncmp(str, "SLEEP", 5))
		printf("%lld %d is sleeping\n", time, id);
	else if (!ft_strncmp(str, "THINK", 5))
		printf("%lld %d is thinking\n", time, id);
	pthread_mutex_unlock(&handler()->write);
}

bool	check_death(t_philo *self)
{
	bool	tog;

	pthread_mutex_lock(&handler()->death);
	if (handler()->dead_philo || dead(self))
		tog = true;
	else
		tog = false;
	pthread_mutex_unlock(&handler()->death);
	return (tog);
}

void	kill(t_philo *self)
{
	if (handler()->n_threads % 2 == 0)
	{
		if (handler()->time_to_die < 2 * handler()->time_to_eat)
			ft_sleep(handler()->time_to_die - handler()->time_to_eat
					- handler()->time_to_sleep);
	}
	else if (handler()->time_to_eat >= handler()->time_to_sleep)
	{
		if (handler()->time_to_die <= 3 * handler()->time_to_eat + 10)
			ft_sleep(handler()->time_to_die - handler()->time_to_eat
					- handler()->time_to_sleep);
	}
	else if (handler()->time_to_die < handler()->time_to_sleep
			+ handler()->time_to_eat + 10)
		ft_sleep(handler()->time_to_die - handler()->time_to_eat
				- handler()->time_to_sleep);
	check_death(self);
}

void	*runtime(void *arg)
{
	t_philo	*self;

	self = arg;
	self->last_meal = current_time();
	self->num_of_times_ate = 0;
	if (handler()->nbr_times_to_eat == 0)
		return (NULL);
	if (self->id % 2 != 0)
	{
		print_menager("THINK", self->id);
		ft_sleep(handler()->time_to_eat);
	}
	while (self->num_of_times_ate < handler()->nbr_times_to_eat)
	{
		if (handler()->n_threads % 2 != 0 && self->id % 2 != 0)
			ft_sleep(0);
		if (handler()->n_threads > 1 && eat(self))
			phi_sleep(self);
		think(self);
		if (check_death(self))
			break ;
	}
	return (NULL);
}
