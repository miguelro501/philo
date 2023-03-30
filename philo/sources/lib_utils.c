/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:16:15 by miguelro          #+#    #+#             */
/*   Updated: 2023/03/29 13:00:38 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
		ptr[i++] = 0;
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(size * nitems);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nitems * size);
	return (ptr);
}

bool	arg_checker(char **str)
{
	int	i;
	int	j;

	j = 0;
	while (str[++j])
	{
		i = -1;
		while (str[j][++i])
		{
			if (!('0' <= str[j][i] && str[j][i] <= '9'))
				return (false);
		}
	}
	return (true);
}

long long	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long long	value;

	i = 0;
	neg = 1;
	value = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		value = 10 * value + (str[i] - '0');
		if (!(INT_MIN <= value * neg && value * neg <= INT_MAX))
			return (LONG_MAX);
		i++;
	}
	return (value * neg);
}
