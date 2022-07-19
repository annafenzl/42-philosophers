/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:17:05 by afenzl            #+#    #+#             */
/*   Updated: 2022/07/19 12:15:08 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	START THE DOCKER WITH ./START.SH 
	-->RUN valgrind --tool=memcheck ./philo 4 300 100 100
	-->RUN valgrind --tool=drd ./philo 4 300 100 100 
	-->RUN valgrind --tool=helgrind ./philo 4 300 100 100
		-->threads
	
	let them start at the same time
	start time from 00000000
	logic for 1 2 3 philos
	--> one is done
	make all of them live longer
	do the must eat stuff
	need to put a lock around philo->data->death -->race conditions
	// printfs in extra function
	// one philosopher
	// check for death or unlock fork if i cant take second one
*/

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		ft_error(0);
	input_check(argv, &rules);
	printf("amount_phil =  %i\n", rules.amount_phil);
	printf("time_die    =  %li\n", rules.time_die);
	printf("time_eat    =  %li\n", rules.time_eat);
	printf("time_sleep  =  %li\n", rules.time_sleep);
	printf("must_eat    = %i\n", rules.must_eat);
	printf("\n-------------------------\n");
	create(&rules);
	return (0);
}
	// system("leaks philo");
