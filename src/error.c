/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:17:13 by mrehberg          #+#    #+#             */
/*   Updated: 2023/01/23 19:31:00 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/**
 * @brief prints error message and calls clean_up()
 * returns one if everything goes well clean_up() returns 0
 * @return error() returns 1 if everything goes well BEWARE!!!
 */
int	error(int err, t_info *info)
{
	printf("ERROR\n");
	if (err == ERR_MALLOC_FORKS || err == ERR_MALLOC_T_PHILOS || \
		err == ERR_MALLOC_PRINT || err == ERR_MALLOC_MUTEX_FORKS)
		printf("While memory allocation\n");
	if (err == ERR_MUTEX_INIT_FORKS || err == ERR_MUTEX_INIT_PRINT)
		printf("While init mutex\n");
	if (err == ERR_THREAD_CREATE)
		printf("While thread creating\n");
	if (err == ERR_THREAD_JOIN)
		printf("While thread joining\n");
	if (err == ERR_WRONG_INPUT)
		printf("please give me numbers > 0 as input\n");
	if (err == ERR_MUTEX_DESTROY || err == ERR_MUTEX_PRINT_DESTROY)
		printf("While destroying mutex\n");
	return (!clean_up(err, info));
}

int	error_arg(int argc)
{
	if (argc == 5 || argc == 6)
		return (0);
	write(2, "Error\n", 6);
	printf("Wrong number of Arguments\n");
	printf("Please give me the num of Philos, time to die\n");
	printf("time to eat, time to sleep and if you want\n");
	printf("the number of meals they have to eat\n");
	return (1);
}
