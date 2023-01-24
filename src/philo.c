/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:12:41 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/24 11:59:37 by mrehberg         ###   ########.fr       */
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
