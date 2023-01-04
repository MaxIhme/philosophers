/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:18:34 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/02 10:42:16 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sleep_philo(t_philo *philo)
{
	if (dead_or_saturated(philo))
		return (1);
	print_status(philo, STATUS_SLEEP);
	while ((time_from_start() - philo->start_action) < philo->info->time_sleep)
	{
		if (dead_or_saturated(philo)) // die abfrage macht evtl. einen lagg
			return (1);
		usleep(100);
	}
	return (0);
}

int 	think_philo(t_philo *philo)
{
	if (dead_or_saturated(philo))
		return (1);
	//philo->start_action = time_from_start();
	print_status(philo, STATUS_THINK);
	return (0);
}

void	eat_philo_sub(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_first_fork);
	pthread_mutex_lock(philo->mutex_second_fork);
	*philo->first_fork = 1;
	print_status(philo, STATUS_FORK);
	*philo->second_fork = 1;
	print_status(philo, STATUS_FORK);
	print_status(philo, STATUS_EAT);
	philo->last_time_eat = philo->start_action;
	while ((time_from_start() - philo->start_action) < philo->info->time_eat)
		usleep(100);
	*philo->first_fork = 0;
	*philo->second_fork = 0;
	pthread_mutex_unlock(philo->mutex_first_fork);
	pthread_mutex_unlock(philo->mutex_second_fork);
	philo->num_eaten_meals++;
}

/**
 * @brief in the while loop the usleep(1000) with the three conditions before 
 * ensures the right order that the philosophers eat -> that one that is saturated 
 * waits 1 ms, so a philosopher that nearly starves can eat
 *  -> time_from_start() > philo->info->time_die / 5 is a start condition -> don't do this
 * when the program starts
 *  -> if (!*philo->first_fork && !*philo->second_fork) -> when both forks are free
 *  -> if (philo->info->time_die - (time_from_start() - philo->last_time_eat) > (philo->info->time_die / 3))
 * 			-> when a philosopher has more than 1/3 of the die time left he should wait 1 ms 
 */
int	eat_philo(t_philo *philo)
{
	if (DEBUG_PRINT_DOT_ID && DEBUG)
	{
		write(1, ".", 1); // debugging
		printf("%d ", philo->id + 1);
	}
	while(1)
	{
		if (time_from_start() > philo->info->time_die / 5) // hier weiter machen
		{
			if (!*philo->first_fork && !*philo->second_fork)
			{
				if (philo->info->time_die - (time_from_start() - philo->last_time_eat) > (philo->info->time_die / 3)) // num of phios odd
					usleep(1000);
			}
		}
		if (dead_or_saturated(philo))
			return (1);
		if (!*philo->first_fork && !*philo->second_fork)
		{
			eat_philo_sub(philo);
			if (DEBUG_PRINT_MEAL_COUNT && DEBUG)
				printf("--- philo %d has eaten %d meals\n", philo->id + 1, philo->num_eaten_meals); // weg!!
			return (0);
		}
		usleep(100);
	}
	return (0);
}

/**
 * @brief philo->id % 2 == 0 means id's that are even 
 * -> but printed they are uneven (id + 1)
 */
void *welcome_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_time_eat = 0;
	if (philo->id % 2 == 0)
	{
		if (sleep_philo(philo))
			return (NULL);
		if (think_philo(philo))
			return (NULL);
	}
	while (1)
	{
		if (eat_philo(philo))
			return (NULL);
		if (sleep_philo(philo))
			return (NULL);
		if (think_philo(philo))
			return (NULL);
	}
	return (NULL);
}


//beim printen id + 1 machen