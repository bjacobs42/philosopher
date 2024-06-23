/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:13:52 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/31 17:22:26 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	extermination(t_shared_data *data)
{
	pthread_mutex_lock(&data->m_terminate);
	data->termination = true;
	pthread_mutex_unlock(&data->m_terminate);
}

static bool	exterminate(t_philo *philosophers, t_shared_data *data)
{
	int				i;
	int				ate;
	unsigned long	current_time;

	ate = 0;
	i = data->variables[TTL_PHILOS];
	while (i--)
	{
		pthread_mutex_lock(&philosophers->m_self);
		current_time = get_time(data->start_tv);
		if (current_time - philosophers->last_meal
			>= (unsigned long)data->variables[DIE_TIME])
		{
			pthread_mutex_unlock(&philosophers->m_self);
			add_queue(current_time, philosophers->name, DIED, data->log);
			return (true);
		}
		if (philosophers->eat_times >= data->variables[MUST_EAT])
			ate++;
		pthread_mutex_unlock(&philosophers->m_self);
		philosophers = philosophers->next;
	}
	if (data->variables[MUST_EAT] != -1 && ate >= data->variables[TTL_PHILOS])
		return (true);
	return (false);
}

int	monitor(t_philo *philosophers, t_shared_data *data)
{
	pthread_mutex_unlock(&data->m_sync);
	while (true)
	{
		usleep(400);
		if (exterminate(philosophers, data))
			break ;
	}
	extermination(data);
	return (EXIT_SUCCESS);
}
