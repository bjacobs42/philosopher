/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:44:13 by bjacobs           #+#    #+#             */
/*   Updated: 2023/03/31 11:44:16 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

void	add_queue(unsigned long current_time, int name, int type, t_log *log)
{
	pthread_mutex_lock(&log->m_script);
	if (log->queue_size == -1)
	{
		pthread_mutex_unlock(&log->m_script);
		return ;
	}
	log->msg_queue[log->queue_size].type = type;
	log->msg_queue[log->queue_size].name = name;
	log->msg_queue[log->queue_size].time_stamp = current_time;
	log->queue_size++;
	if (log->queue_size >= log->max_size)
	{
		printf("Log messages overflow, Resetting message queue...\n");
		log->queue_size = 0;
	}
	pthread_mutex_unlock(&log->m_script);
}

static int	print_lst(t_log *log)
{
	int			i;
	static char	*msgs[] = {DIED_MSG, EAT_MSG, THINK_MSG, SLEEP_MSG, FORK_MSG};

	i = 0;
	while (i < log->lst_size)
	{
		printf("%lu %d %s\n", log->msg_lst[i].time_stamp,
			log->msg_lst[i].name, msgs[log->msg_lst[i].type]);
		if (log->msg_lst[i].type == DIED)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	swap_lst(t_log *log)
{
	t_msg_data	*tmp;

	tmp = log->msg_queue;
	log->msg_queue = log->msg_lst;
	log->msg_lst = tmp;
	log->lst_size = log->queue_size;
	if (log->queue_size > 0)
		log->queue_size = 0;
}

void	*announcer(void *param)
{
	t_log			*log;
	t_shared_data	*data;

	data = (t_shared_data *)param;
	log = data->log;
	while (!terminate(data) || log->lst_size > 0)
	{
		usleep(500);
		pthread_mutex_lock(&log->m_script);
		swap_lst(log);
		pthread_mutex_unlock(&log->m_script);
		if (log->lst_size > 0)
		{
			if (print_lst(log) == EXIT_FAILURE)
				break ;
		}
	}
	return (NULL);
}
