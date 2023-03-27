/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:24:22 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/27 10:28:04 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initializer(void)
{
	int	i;

	i = -1;
	(handler())->philos = ft_calloc(sizeof(t_philo), handler()->n_threads);
	(handler())->forks = ft_calloc(sizeof(t_fork), handler()->n_threads);
	handler()->start_time = get_time();
	while (++i < handler()->n_threads)
	{
		if (pthread_mutex_init(&handler()->forks[i].fork, NULL))
			error("Error creating mutex");
		handler()->forks[i].id = i;
		handler()->philos[i].id = i;
	}
}

void	create_philos(void)
{
	int	i;

	i = -1;
	initializer();
	while (++i < handler()->n_threads)
	{
		if (pthread_create(&handler()->philos[i].thread, NULL, runtime,
				(void *)&handler()->philos[i]))
			error("Error creating threads");
	}
	i = -1;
	while (++i < handler()->n_threads)
	{
		if (pthread_join(handler()->philos[i].thread, NULL))
			error("Error joining threads");
	}
	i = -1;
	while (++i < handler()->n_threads)
	{
		if (pthread_mutex_destroy(&handler()->forks[i].fork)
			&& pthread_mutex_destroy(&handler()->death))
			error("Error destroying fork");
	}
}

int	main(int ac, char **av)
{
	if (ac != 6 && ac != 5)
		error("Invalid number of parameters");
	if (!arg_checker(av))
		error("Invalid parameters");
	handler()->n_threads = ft_atoi(av[1]);
	handler()->time_to_die = ft_atoi(av[2]);
	handler()->time_to_eat = ft_atoi(av[3]);
	handler()->time_to_sleep = ft_atoi(av[4]);
	handler()->dead_philo = false;
	pthread_mutex_init(&handler()->death, NULL);
	if (ac == 6)
		handler()->nbr_times_to_eat = ft_atoi(av[5]);
	else
		handler()->nbr_times_to_eat = __INT_MAX__;
	create_philos();
	return (0);
}
