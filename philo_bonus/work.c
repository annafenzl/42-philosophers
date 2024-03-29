/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:12 by afenzl            #+#    #+#             */
/*   Updated: 2022/07/29 15:47:43 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks_and_eat(t_philo *philo)
{
	take_forks(philo);
	eat(philo);
	sem_post(philo->data->num_forks);
	sem_post(philo->data->num_forks);
	must_eat(philo);
	check_if_dead(philo);
}

void	take_nap(t_philo *philo)
{
	print_feedback(philo, 's');
	if (philo->limit < get_current_time_ms() + philo->data->time_sleep)
	{
		sleep_ms(philo->limit - get_current_time_ms());
		check_if_dead(philo);
		exit (1);
	}
	sleep_ms(philo->data->time_sleep);
	check_if_dead(philo);
}

void	thinking(t_philo *philo)
{
	print_feedback(philo, 't');
}

void	philo_start(t_philo *philo)
{
	sleep_ms(philo->data->birth - get_current_time_ms());
	print_feedback(philo, 't');
	philo->limit = get_current_time_ms() + philo->data->time_die;
	if ((philo->number & 1) == 1 && philo->data->amount_phil > 1)
		sleep_ms(3);
	while (true)
	{
		take_forks_and_eat(philo);
		philo->limit = get_current_time_ms() + philo->data->time_die;
		take_nap(philo);
		thinking(philo);
	}
}
