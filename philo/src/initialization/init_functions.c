/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:06:50 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/24 20:58:29 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_philo *philosophers, t_shared_data *data)
{
	int	amount;

	gettimeofday(&data->start_tv, NULL);
	amount = data->variables[TTL_PHILOS];
	while (amount--)
	{
		if (pthread_create(&philosophers->thread,
				NULL, &routine, philosophers) != 0)
			return (EXIT_FAILURE);
		philosophers = philosophers->next;
	}
	if (pthread_create(&data->log->thread, NULL, &announcer, data) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_log	*init_announcer(t_shared_data *data)
{
	t_log	*log;

	log = (t_log *)malloc(sizeof(t_log));
	if (!log)
		return (NULL);
	log->max_size = data->variables[TTL_PHILOS] * 100;
	log->msg_lst = (t_msg_data *)malloc(sizeof(t_msg_data) * log->max_size);
	log->msg_queue = (t_msg_data *)malloc(sizeof(t_msg_data) * log->max_size);
	if (!log->msg_lst || !log->msg_queue)
		return (denouncer(log), NULL);
	if (pthread_mutex_init(&log->m_script, NULL) != 0)
		return (denouncer(log), NULL);
	log->queue_size = 0;
	log->lst_size = 0;
	return (log);
}

t_shared_data	*init_data(t_shared_data *data, char **av)
{
	if (pthread_mutex_init(&data->m_terminate, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->m_sync, NULL) != 0)
		return (pthread_mutex_destroy(&data->m_terminate), NULL);
	data->termination = false;
	data->variables[TTL_PHILOS] = ft_atoi(av[1]);
	data->variables[DIE_TIME] = ft_atoi(av[2]);
	data->variables[EAT_TIME] = ft_atoi(av[3]);
	data->variables[SLEEP_TIME] = ft_atoi(av[4]);
	data->log = init_announcer(data);
	if (!data->log)
		return (clear_data(data), NULL);
	if (av[5])
		data->variables[MUST_EAT] = ft_atoi(av[5]);
	else
		data->variables[MUST_EAT] = -1;
	return (data);
}
