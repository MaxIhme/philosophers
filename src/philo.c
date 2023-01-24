/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:12:41 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/24 10:57:49 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * @brief my functions return 0 when they work fine
 * only error() returns 1 if it's done
 * termination of allocs and mutexes will be done in error() -> terminate()
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_info	info;

	if (init_info(&info, argc, argv))
		return (1);
	if (init_mutex(&info))
		return (1);
	if (init_philo(&info))
		return (1);
	if (create_philos(&info))
		return (1);
	join_philos(&info);
	clean_up(CLEAN_UP_EVERYTHING, &info);
	return (0);
}

//timingtest anruland

//verschiedenen input testen minus 0 buchstaben etc.
	// auf leaks überprüfen

	//init aufräumen und die errors vervollständigen

// Philo test
// - Do not test with more than 200 philosophers
// - Do not test with time_to_ die or time_to_eat or time_to_sleep under 60 ms
// - Test with 1 800 200 200, the philosopher should not eat and should die!
// - Test with 5 800 200 200, no one should die!
// - Test with 5 800 200 200 7, no one should die and the simulation 
	// should stop when all the philosopher has eaten at least 7 times each.
// - Test with 4 410 200 200, no one should die!
// - Test with 4 310 200 100, a philosopher should die!
// - Test with 2 philosophers and check the different times (a death delayed 
	// by more than 10 ms is unacceptable).
// - Test with your values to check all the rules. Check if a philosopher 
	// dies at the right time if they don't steal forks, etc.