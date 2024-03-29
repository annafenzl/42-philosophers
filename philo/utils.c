/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:16:14 by afenzl            #+#    #+#             */
/*   Updated: 2022/08/02 17:28:39 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_numcpy(int i, long res, char *p)
{
	long	tmp;

	while (p[i] != '\0')
	{
		tmp = res;
		if (p[i] >= '0' && p[i] <= '9')
		{
			res = res * 10 + p[i] - '0';
			i++;
		}
		else
			return (-1);
		if ((tmp < 0 && res > 0) || (tmp > 0 && res < 0))
			return (-1);
	}
	return (res);
}

long	atoi_check(const char *str)
{
	int				i;
	long			res;
	int				n;
	char			*p;

	i = 0;
	res = 0;
	n = 1;
	p = (char *)str;
	while (p[i] == ' ' || p[i] == '\t')
		i++;
	if (p[i] == '-' || p[i] == '+')
	{
		if (p[i + 1] == '\0')
			return (-1);
		if (p[i] == '-')
			n = -1;
		i++;
	}
	res = ft_numcpy(i, res, p);
	return (res * n);
}

int	print_feedback(t_philo *philo, enum e_act act)
{
	long	birth;

	birth = philo->data->birth;
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->death == false)
	{
		if (act == think)
			printf("%ld %d is thinking\n", timestamp(birth), philo->number);
		else if (act == nap)
			printf("%ld %d is sleeping\n", timestamp(birth), philo->number);
		else if (act == eat)
			printf("%ld %d is eating\n", timestamp(birth),
				philo->number);
		else if (act == take)
			printf("%ld %d has taken a fork\n", timestamp(birth), philo->number);
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (1);
}

void	unlock_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
