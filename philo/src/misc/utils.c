/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:30:40 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/08 20:30:03 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(struct timeval start)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		return (0);
	return ((current.tv_sec * 1000 + current.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000));
}

bool	terminate(t_shared_data *data)
{
	bool	terminate;

	pthread_mutex_lock(&data->m_terminate);
	terminate = data->termination;
	pthread_mutex_unlock(&data->m_terminate);
	return (terminate);
}

void	my_sleep(t_shared_data *data, unsigned long wait_time)
{
	unsigned long	end_time;

	end_time = get_time(data->start_tv) + wait_time;
	while (get_time(data->start_tv) < end_time)
	{
		usleep(200);
		if (terminate(data))
			break ;
	}
}
