/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:18:34 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/24 10:08:59 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// die abfrage line 23 macht evtl. einen lagg
int	sleep_philo(t_philo *philo)
{
	if (dead_or_saturated(philo))
		return (1);
	print_status(philo, STATUS_SLEEP);
	while ((time_from_start() - philo->start_action) < philo->info->time_sleep)
	{
		if (dead_or_saturated(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

int	think_philo(t_philo *philo)
{
	if (dead_or_saturated(philo))
		return (1);
	print_status(philo, STATUS_THINK);
	return (0);
}

/**
 * @brief 
 * 
 * @param philo 
 */
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
 * ensures the right order that the philosophers eat -> that one ..
 * that is saturated waits 1 ms, so a philosopher that nearly starves can eat
 *  -> time_from_start() > philo->info->time_die / 5 is a start condition -> ..
 * don't do this when the program starts
 *  -> if (!*philo->first_fork && !*philo->second_fork) -> when both forks 
 * are free
 *  -> if (philo->info->time_die - (time_from_start() - philo->last_time_eat) >
 *  (philo->info->time_die / 3)) -> when a philosopher has more than 1/3 of the 
 * die time left he should wait 1 ms -> because at max you can have 3 groups, 
 * the odd number of philos, the even number of philos and one alone (if odd 
 * number of philos). So if a philo has more then 1/3 of it's deathtime left, 
 * it can wait a 1/3 of it's deathtime that another one can eat.. and start 
 * eating after that.
 */
int	eat_philo(t_philo *philo)
{
	while (1)
	{
		if (time_from_start() > philo->info->time_die / 5)
		{
			if (!*philo->first_fork && !*philo->second_fork)
			{
				if (philo->info->time_die - (time_from_start() - \
					philo->last_time_eat) > (philo->info->time_die / 3))
					usleep(1000);
			}
		}
		if (dead_or_saturated(philo))
			return (1);
		if (!*philo->first_fork && !*philo->second_fork)
		{
			eat_philo_sub(philo);
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
void	*welcome_philo(void *arg)
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
