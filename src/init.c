/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 07:20:15 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/24 10:57:32 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_info(t_info *info, int argc, char **argv)
{
	if (error_arg(argc))
		return (1);
	info->num_philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_meals = ft_atoi(argv[5]);
	else
		info->num_meals = 0;
	info->philo_died = 0;
	if (info->num_philos <= 0 || info->time_die <= 0 || \
		info->time_eat <= 0 || info->time_sleep <= 0)
		return (error(ERR_WRONG_INPUT, info));
	info->forks = malloc(sizeof(int) * info->num_philos);
	if (info->forks == NULL)
		return (error(ERR_MALLOC_FORKS, info));
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	info->mutex_forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (info-> mutex_forks == NULL)
		return (error(ERR_MALLOC_MUTEX_FORKS, info));
	i = -1;
	while (++i < info->num_philos)
	{
		if (pthread_mutex_init(&info->mutex_forks[i], NULL) != 0)
			return (error(ERR_MUTEX_INIT_FORKS, info));
	}
	if (pthread_mutex_init(&info->mutex_print, NULL) != 0)
		return (error(ERR_MUTEX_INIT_PRINT, info));
	return (0);
}

void	init_philo_sub(t_info *info, t_init_philo *p, int i)
{
	info->philo[i].id = i;
	info->philo[i].info = info;
	if (i % 2)
	{
		info->philo[i].mutex_first_fork = &info->mutex_forks[i];
		info->philo[i].mutex_second_fork = p->m_right_fork;
		info->philo[i].first_fork = p->left_fork;
		info->philo[i].second_fork = p->right_fork;
	}
	else
	{
		info->philo[i].mutex_first_fork = p->m_right_fork;
		info->philo[i].mutex_second_fork = &info->mutex_forks[i];
		info->philo[i].first_fork = p->right_fork;
		info->philo[i].second_fork = p->left_fork;
	}
	info->philo[i].num_eaten_meals = 0;
}

/**
 * @brief method against dead locks -> look if the forks are free -> 
 * there are mutexes for forks and then forks itself. 
 * Because you can't see if the mutex is free or not.
 *  first grab the fork 
 * with the odd number
 * then the other one. (mutex_first_fork) (mutex_second_fork)->in struct
 * -> if the process id is odd (i % 2) mutex_first_fork is 
 * the same number (left fork)
 * and mutex_second_fork is id + 1 (right fork)
 * -> if the process id is even mutex_first_fork is id + 1 (right fork)
 * and mutex_second_fork is id (left fork)
 */
int	init_philo(t_info *info)
{
	int				i;
	t_init_philo	p;

	i = -1;
	info->philo = malloc(sizeof(t_philo) * info->num_philos);
	if (!info->philo)
		return (error(ERR_MALLOC_T_PHILOS, info));
	while (++i < info->num_philos)
	{
		p.m_left_fork = &info->mutex_forks[i];
		p.left_fork = &info->forks[i];
		if (i == info->num_philos - 1)
		{
			p.m_right_fork = &info->mutex_forks[0];
			p.right_fork = &info->forks[0];
		}
		else
		{
			p.m_right_fork = &info->mutex_forks[i + 1];
			p.right_fork = &info->forks[i + 1];
		}
		init_philo_sub(info, &p, i);
	}
	return (0);
}

int	create_philos(t_info *info)
{
	int	i;

	i = -1;
	time_from_start();
	if (info->num_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		printf("%d 1 died\n", info->time_die);
		clean_up(CLEAN_UP_EVERYTHING, info);
		return (1);
	}
	while (++i < info->num_philos)
	{
		if (pthread_create(&info->philo[i].thread, NULL, \
			&welcome_philo, &info->philo[i]))
			return (error(ERR_THREAD_CREATE, info));
	}
	return (0);
}
