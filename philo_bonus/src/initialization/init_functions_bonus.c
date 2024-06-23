/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:06:50 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/25 16:39:21 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_procs(t_philo *philo, t_shared_data *data)
{
	int	i;
	int	*pids;

	pids = (int *)malloc(sizeof(int) * data->variables[TTL_PHILOS]);
	if (!pids)
		return (EXIT_FAILURE);
	i = 0;
	gettimeofday(&data->start_tv, NULL);
	while (i < data->variables[TTL_PHILOS])
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (free(pids), EXIT_FAILURE);
		if (pids[i] == 0)
			routine(philo, data);
		philo->pid = pids[i];
		philo = philo->next;
		i++;
	}
	free(pids);
	return (EXIT_SUCCESS);
}

static int	init_semaphores(t_shared_data *data, int ttl_philos)
{
	sem_unlink(SEM_SYNC);
	data->sem_sync = sem_open(SEM_SYNC, O_CREAT, 0666, 0);
	if (data->sem_sync == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink(SEM_TERM);
	data->sem_terminate = sem_open(SEM_TERM, O_CREAT, 0666, 0);
	if (data->sem_terminate == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink(SEM_ATE);
	data->sem_ate = sem_open(SEM_ATE, O_CREAT, 0666, 0);
	if (data->sem_ate == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink(SEM_FORK);
	data->sem_forks = sem_open(SEM_FORK, O_CREAT, 0666, ttl_philos);
	if (data->sem_forks == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink(SEM_PRINT);
	data->sem_print = sem_open(SEM_PRINT, O_CREAT, 0666, 1);
	if (data->sem_print == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_shared_data	*init_data(t_shared_data *data, char **av)
{
	data->variables[TTL_PHILOS] = ft_atoi(av[1]);
	if (init_semaphores(data, data->variables[TTL_PHILOS]) != EXIT_SUCCESS)
		return (clear_data(data), NULL);
	data->variables[DIE_TIME] = ft_atoi(av[2]);
	data->variables[EAT_TIME] = ft_atoi(av[3]);
	data->variables[SLEEP_TIME] = ft_atoi(av[4]);
	if (av[5])
		data->variables[MUST_EAT] = ft_atoi(av[5]);
	else
		data->variables[MUST_EAT] = -1;
	return (data);
}
