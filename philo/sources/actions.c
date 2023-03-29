/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:18:50 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/29 18:52:25 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat_aux_aux(t_philo *self)
{
	print_menager("FORK", self->id);
	print_menager("EAT", self->id);
	self->last_meal = current_time();
	if (handler()->time_to_die <= handler()->time_to_eat)
		ft_sleep(handler()->time_to_die);
	else
		ft_sleep(handler()->time_to_eat);
	self->num_of_times_ate++;
	return (true);
}

bool	eat_aux(bool ate, t_fork *l_fork, t_fork *r_fork, t_philo *self)
{
	if (!pthread_mutex_lock(&l_fork->fork))
	{
		if (check_death(self))
		{
			pthread_mutex_unlock(&l_fork->fork);
			return (false);
		}
		print_menager("FORK", self->id);
		if (!pthread_mutex_lock(&r_fork->fork))
		{
			if (check_death(self))
			{
				pthread_mutex_unlock(&r_fork->fork);
				pthread_mutex_unlock(&l_fork->fork);
				return (false);
			}
			ate = eat_aux_aux(self);
			pthread_mutex_unlock(&r_fork->fork);
		}
		pthread_mutex_unlock(&l_fork->fork);
	}
	return (ate);
}

bool	eat(t_philo *self)
{
	t_fork	*l_fork;
	t_fork	*r_fork;
	int		id;
	bool	ate;

	id = self->id;
	ate = false;
	self->thinking = false;
	l_fork = &handler()->forks[id];
	if (id + 1 >= handler()->n_threads)
	{
		l_fork = &handler()->forks[0];
		r_fork = &handler()->forks[id];
	}
	else
		r_fork = &handler()->forks[id + 1];
	ate = eat_aux(ate, l_fork, r_fork, self);
	return (ate);
}

void	phi_sleep(t_philo *self)
{
	if (check_death(self))
		return ;
	self->thinking = false;
	print_menager("SLEEP", self->id);
	if (handler()->time_to_die <= handler()->time_to_sleep
		+ handler()->time_to_eat)
		ft_sleep(handler()->time_to_die - handler()->time_to_eat);
	else
		ft_sleep(handler()->time_to_sleep);
}

void	think(t_philo *self)
{
	if (check_death(self))
		return ;
	if (!self->thinking)
	{
		self->thinking = true;
		print_menager("THINK", self->id);
		kill(self);
		ft_sleep(handler()->time_to_eat - handler()->time_to_sleep + 10);
	}
}
