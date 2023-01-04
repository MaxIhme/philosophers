/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:12:02 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/02 10:54:28 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

//*********************************************************//
//**                FLAGS                               **//

# define ERR_MALLOC_FORKS 1
# define ERR_MALLOC_MUTEX_FORKS 2
# define ERR_MUTEX_INIT_FORKS 3
# define ERR_MALLOC_PRINT 4
# define ERR_MUTEX_INIT_PRINT 5
# define ERR_MALLOC_T_PHILOS 6
# define ERR_THREAD_CREATE 7
# define ERR_THREAD_JOIN 8
# define ERR_WRONG_INPUT 9
# define ERR_MUTEX_DESTROY 10
# define ERR_MUTEX_PRINT_DESTROY 11

# define STATUS_SLEEP 12
# define STATUS_THINK 13
# define STATUS_EAT 14
# define STATUS_FORK 15
# define STATUS_DEAD 16

# define CLEAN_UP_EVERYTHING 17

//*********************************************************//
//**                DEBUGGING                           **//

# define DEBUG 0
# define DEBUG_PRINT_MEAL_COUNT 1
# define DEBUG_PRINT_DOT_ID 0


//*********************************************************//
//**                STRUCTURES                          **//

typedef struct	s_philo
{
	int				id;
	pthread_t		thread;
	int				start_action;
	int				last_time_eat;
	int				num_eaten_meals;
	int				*first_fork;
	int				*second_fork;
	pthread_mutex_t	*mutex_first_fork;
	pthread_mutex_t	*mutex_second_fork;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	int				philo_died;
	int				*forks;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_print;
	t_philo			*philo;	
}	t_info;

//*********************************************************//
//**                FUNCTIONS                           **//
//*******************************************************//

//**** INIT.C ****//

int	init_info(t_info *info, int argc, char **argv);
int	init_mutex(t_info *info);
int	init_philo(t_info *info);
int	create_philos(t_info *info);

//**** FT_ATOI.C ****//

int			ft_atoi(const char *str);

//**** ERROR.C ****//

int	error(int err, t_info *info);
int	error_arg(int argc);

//**** PHILO_ACTIONS.C ****//

int		sleep_philo(t_philo *philo);
int 	think_philo(t_philo *philo);
void	eat_philo_sub(t_philo *philo);
int		eat_philo(t_philo *philo);
void	*welcome_philo(void *arg);

//**** UTILS.C ****//

int		time_from_start(void);
void	print_status(t_philo *philo, int status);
int		dead_or_saturated(t_philo *philo);

//**** CLEAN_UP.C ****//

int		join_philos(t_info *info);
void	clean_up_mutex(pthread_mutex_t	*mutex, t_info *info);
int		clean_up(int err, t_info *info);

#endif
