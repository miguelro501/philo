/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:24:20 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/27 10:46:59 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				num_of_times_ate;
	long long		last_meal;
	pthread_t		thread;
	bool			thinking;

}					t_philo;

typedef struct s_handler
{
	t_philo			*philos;
	t_fork			*forks;
	int				n_threads;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		nbr_times_to_eat;
	long long		start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	bool			dead_philo;
}					t_handler;

t_handler			*handler(void);
long long			get_time(void);
void				*runtime(void *asmr);
int					error(char *str);
void				ft_sleep(long long time);
void				print_menager(char *str, int id);
void				phi_sleep(t_philo *self);
void				think(t_philo *self);
bool				dead(t_philo *self);
bool				eat(t_philo *self);
long long			current_time(void);
void				*ft_calloc(size_t nitems, size_t size);
int					ft_atoi(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
bool				arg_checker(char **str);

#endif