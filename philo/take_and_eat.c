/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_and_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:49:36 by afenzl            #+#    #+#             */
/*   Updated: 2022/08/02 17:27:44 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	die_alone(t_philo *philo)
{
	print_feedback(philo, take);
	sleep_ms(philo->data->time_die);
	printf("%ld %d died\n", timestamp(philo->data->birth), philo->number);
	return (1);
}

int	uneven_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_feedback(philo, take);
	if (check_if_dead(philo) == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	print_feedback(philo, take);
	return (0);
}

int	even_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_feedback(philo, take);
	if (check_if_dead(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	print_feedback(philo, take);
	return (0);
}

// uneven take left forks
// even take right forks
// -->no race conditions
int	who_takes_forks(t_philo *philo)
{
	if ((philo->number & 1) == 1)
		return (uneven_take_forks(philo));
	else
		return (even_take_forks(philo));
	if (check_if_dead(philo) == 1)
	{
		unlock_both_forks(philo);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	print_feedback(philo, eat);
	if (philo->limit <= get_current_time_ms() + philo->data->time_eat)
	{
		while (get_current_time_ms() < philo->limit)
			continue ;
		check_if_dead(philo);
		return (1);
	}
	sleep_ms(philo->data->time_eat);
	philo->times_eaten++;
	if (must_eat_checker(philo) == 1)
		return (1);
	return (check_if_dead(philo));
}
