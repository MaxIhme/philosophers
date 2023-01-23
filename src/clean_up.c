/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:30:09 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/23 19:30:32 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	join_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
	{
		if (pthread_join(info->philo[i].thread, NULL))
			return (error(ERR_THREAD_JOIN, info));
	}
	return (0);
}

void	clean_up_mutex(pthread_mutex_t	*mutex, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
	{
		if (pthread_mutex_destroy(&mutex[i]) != 0)
		{
			error(ERR_MUTEX_DESTROY, info);
		}
	}
}

/**
 * @brief if an error comes in it does only one NEW task 
 * and then calls the function again with the error before
 */
int	clean_up(int err, t_info *info)
{
	if (err == ERR_MALLOC_MUTEX_FORKS)
		free (info->forks);
	if (err == ERR_MUTEX_INIT_FORKS)
	{
		free (info->mutex_forks);
		clean_up(ERR_MALLOC_MUTEX_FORKS, info);
	}
	if (err == ERR_MUTEX_INIT_PRINT)
	{
		clean_up_mutex(info->mutex_forks, info);
		clean_up(ERR_MUTEX_INIT_FORKS, info);
	}
	if (err == ERR_MALLOC_T_PHILOS)
	{
		if (pthread_mutex_destroy(&info->mutex_print) != 0)
			error(ERR_MUTEX_PRINT_DESTROY, info);
		clean_up(ERR_MUTEX_INIT_PRINT, info);
	}
	if (err == ERR_THREAD_CREATE || err == CLEAN_UP_EVERYTHING)
	{
		free (info->philo);
		clean_up(ERR_MALLOC_T_PHILOS, info);
	}
	return (0);
}
