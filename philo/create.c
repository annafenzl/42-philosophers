/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:46:30 by afenzl            #+#    #+#             */
/*   Updated: 2022/07/22 14:29:27 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos(t_rules *rules)
{
	int	i;

	i = 0;
	rules->birth = -1;
	pthread_mutex_init(&(rules->lock), NULL);
	rules->birth = get_current_time_ms() + 3;
	while (i < rules->amount_phil)
	{
		pthread_mutex_init(&(rules->forks[i]), NULL);
		rules->philo[i].number = i + 1;
		pthread_create(&rules->id_philo[i], NULL,
			&work, &rules->philo[i]);
		i++;
	}
}

void	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->amount_phil)
	{
		pthread_join(rules->id_philo[i], NULL);
		i++;
	}
	i = 0;
	while (i < rules->amount_phil)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(rules->lock));
}
