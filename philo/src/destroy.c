/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:10:10 by bjacobs           #+#    #+#             */
/*   Updated: 2023/03/29 18:46:01 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	join_threads(t_philo *philosophers, t_shared_data *data)
{
	int	i;

	pthread_join(data->log->thread, NULL);
	if (data->variables[TTL_PHILOS] <= 1)
		return ;
	i = 0;
	while (i < data->variables[TTL_PHILOS])
	{
		pthread_join(philosophers->thread, NULL);
		philosophers = philosophers->next;
		i++;
	}
}

void	denouncer(t_log *log)
{
	if (!log)
		return ;
	if (pthread_mutex_lock(&log->m_script) == 0)
	{
		pthread_mutex_unlock(&log->m_script);
		pthread_mutex_destroy(&log->m_script);
	}
	if (log->msg_lst)
	{
		free(log->msg_lst);
		log->msg_lst = NULL;
	}
	if (log->msg_queue)
	{
		free(log->msg_queue);
		log->msg_queue = NULL;
	}
	free(log);
	log = NULL;
}

void	clear_data(t_shared_data *data)
{
	if (!data)
		return ;
	pthread_mutex_destroy(&data->m_terminate);
	pthread_mutex_destroy(&data->m_sync);
	denouncer(data->log);
}

void	destroy(t_philo **philosophers)
{
	t_philo			*tmp;
	t_shared_data	*data;

	data = (*philosophers)->data;
	join_threads(*philosophers, data);
	clear_data(data);
	while (data->variables[TTL_PHILOS]-- && *philosophers)
	{
		tmp = (*philosophers)->next;
		pthread_mutex_destroy(&(*philosophers)->m_self);
		pthread_mutex_destroy(&(*philosophers)->m_rfork);
		free(*philosophers);
		*philosophers = tmp;
	}
}
