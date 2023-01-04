/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:46:25 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/02 11:02:44 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * @brief returns the time from the starttime in msec
 * if it is called the first time returns 0 and saves the time
 */
int	time_from_start(void)
{
	static struct timeval	start_time;
	struct timeval			time_mem;
	static int				first = 0;
	long					buf;

	gettimeofday(&time_mem, NULL);
	if (first++ == 0)
	{
		start_time = time_mem;
		return (0);
	}
	buf = (((time_mem.tv_sec - start_time.tv_sec) * 1000) + \
		((time_mem.tv_usec - start_time.tv_usec) / 1000));
	return ((int)buf);
}

/**
 * @brief the extra test (redundancy) (&& !philo->info->philo_died) is
 * because I hat philos that would write something after one philo died
 */
void	print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->info->mutex_print);
	if (status == STATUS_SLEEP && !philo->info->philo_died)
		printf("%d %d is sleeping\n", philo->start_action = time_from_start(), \
			philo->id + 1);
	if (status == STATUS_THINK && !philo->info->philo_died)
		printf("%d %d is thinking\n", philo->start_action = time_from_start(), \
			philo->id + 1);
	if (status == STATUS_EAT && !philo->info->philo_died)
		printf("%d %d is eating\n", philo->start_action = time_from_start(), \
			philo->id + 1);
	if (status == STATUS_FORK && !philo->info->philo_died)
		printf("%d %d has taken a fork\n", time_from_start(), philo->id + 1);
	if (status == STATUS_DEAD)
		printf("%d %d died\n", time_from_start(), philo->id + 1);
	pthread_mutex_unlock(&philo->info->mutex_print);
}

int	dead_or_saturated(t_philo *philo)
{
	if (philo->info->philo_died)
		return (1);
	if ((time_from_start() - philo->last_time_eat) > philo->info->time_die)
	{
		philo->info->philo_died = 1;
		print_status(philo, STATUS_DEAD);
		return (1);
	}
	if ((philo->num_eaten_meals >= philo->info->num_meals) && \
		philo->info->num_meals)
		return (1);
	return (0);
}
