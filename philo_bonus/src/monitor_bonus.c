/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:13:52 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/31 21:32:08 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "printing.h"
#include <signal.h>
#include <sys/wait.h>

static void	start_simulation(t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < data->variables[TTL_PHILOS])
	{
		sem_wait(data->sem_ate);
		i++;
	}
	sem_post(data->sem_sync);
}

static void	*dietician(void *param)
{
	int				i;
	t_shared_data	*data;

	i = 0;
	data = (t_shared_data *)param;
	sem_wait(data->sem_sync);
	sem_post(data->sem_sync);
	while (i < data->variables[TTL_PHILOS])
	{
		sem_wait(data->sem_ate);
		i++;
	}
	sem_post(data->sem_terminate);
	sem_wait(data->sem_print);
	return (NULL);
}

int	monitor(t_philo *philosophers, t_shared_data *data)
{
	int			i;
	pthread_t	pthr_dietician;

	if (data->variables[MUST_EAT] != -1)
	{
		if (pthread_create(&pthr_dietician, NULL, dietician, (void *)data))
			return (EXIT_FAILURE);
		pthread_detach(pthr_dietician);
	}
	i = 0;
	start_simulation(data);
	sem_wait(data->sem_terminate);
	while (i < data->variables[TTL_PHILOS])
	{
		kill(philosophers->pid, SIGTERM);
		philosophers = philosophers->next;
		i++;
	}
	return (EXIT_SUCCESS);
}
