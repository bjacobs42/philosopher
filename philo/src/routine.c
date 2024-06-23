/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:11:09 by bjacobs           #+#    #+#             */
/*   Updated: 2023/06/01 17:17:31 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	sync_philos(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_sync);
	pthread_mutex_unlock(&philo->data->m_sync);
	pthread_mutex_lock(&philo->m_self);
	philo->last_meal = get_time(philo->data->start_tv);
	pthread_mutex_unlock(&philo->m_self);
	if (philo->name % 2)
		usleep(200);
}

static void	take_fork(t_philo *philo, t_shared_data *data)
{
	pthread_mutex_lock(&philo->m_rfork);
	add_queue(get_time(data->start_tv), philo->name,
		TAKING_FORK, data->log);
	pthread_mutex_lock(philo->m_lfork);
	add_queue(get_time(data->start_tv), philo->name,
		TAKING_FORK, data->log);
}

static void	eat(t_philo *philo, t_shared_data *data)
{
	unsigned long	current_time;

	current_time = get_time(data->start_tv);
	add_queue(current_time, philo->name, EATING, data->log);
	pthread_mutex_lock(&philo->m_self);
	philo->last_meal = current_time;
	pthread_mutex_unlock(&philo->m_self);
	my_sleep(data, data->variables[EAT_TIME]);
	pthread_mutex_lock(&philo->m_self);
	philo->eat_times++;
	pthread_mutex_unlock(&philo->m_self);
	pthread_mutex_unlock(&philo->m_rfork);
	pthread_mutex_unlock(philo->m_lfork);
}

void	*routine(void *param)
{
	t_shared_data	*data;
	t_philo			*philosopher;

	philosopher = (t_philo *)param;
	data = philosopher->data;
	sync_philos(philosopher);
	while (true)
	{
		add_queue(get_time(data->start_tv), philosopher->name,
			THINKING, data->log);
		take_fork(philosopher, data);
		eat(philosopher, data);
		if (terminate(data))
			return (NULL);
		add_queue(get_time(data->start_tv), philosopher->name,
			SLEEPING, data->log);
		my_sleep(data, data->variables[SLEEP_TIME]);
		if (terminate(data))
			return (NULL);
	}
	return (NULL);
}
