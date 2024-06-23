/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:11:09 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/31 17:35:44 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "printing.h"

static void	put_action(t_philo *philo, int type)
{
	static char	*msgs[] = {DIED_MSG, EAT_MSG, THINK_MSG, SLEEP_MSG, FORK_MSG};

	sem_wait(philo->data->sem_print);
	printf("%lu %d %s\n", get_time(philo->data->start_tv), \
			philo->name, msgs[type]);
	if (type == DIED)
		return ;
	sem_post(philo->data->sem_print);
}

static void	grabneat(t_philo *philo, t_shared_data *data)
{
	unsigned long	current_time;

	sem_wait(data->sem_forks);
	put_action(philo, TAKING_FORK);
	sem_wait(data->sem_forks);
	put_action(philo, TAKING_FORK);
	current_time = get_time(data->start_tv);
	put_action(philo, EATING);
	sem_wait(philo->sem_self);
	philo->last_meal = current_time;
	sem_post(philo->sem_self);
	my_sleep(data, data->variables[EAT_TIME]);
	sem_wait(philo->sem_self);
	philo->eat_times++;
	sem_post(philo->sem_self);
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
}

void	*observer(void *param)
{
	unsigned long	current_time;
	t_philo			*philo;
	t_shared_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	while (true)
	{
		usleep(500);
		sem_wait(philo->sem_self);
		current_time = get_time(data->start_tv);
		if (current_time - philo->last_meal \
				>= (unsigned long)data->variables[DIE_TIME])
			break ;
		if (data->variables[MUST_EAT] != -1
			&& philo->eat_times >= data->variables[MUST_EAT])
		{
			data->variables[MUST_EAT] = -1;
			sem_post(data->sem_ate);
		}
		sem_post(philo->sem_self);
	}
	put_action(philo, DIED);
	sem_post(philo->data->sem_terminate);
	return (exit(0), NULL);
}

static int	sync_philos(t_philo *philo)
{
	pthread_t	observer_thread;

	sem_unlink(philo->name_self);
	philo->sem_self = sem_open(philo->name_self, O_CREAT, 0666, 0);
	if (philo->sem_self == SEM_FAILED)
		return (EXIT_FAILURE);
	if (pthread_create(&observer_thread, NULL, &observer, philo))
		return (put_error(THREAD_FAILURE_MSG), EXIT_FAILURE);
	pthread_detach(observer_thread);
	sem_post(philo->data->sem_ate);
	sem_wait(philo->data->sem_sync);
	sem_post(philo->data->sem_sync);
	philo->last_meal = get_time(philo->data->start_tv);
	sem_post(philo->sem_self);
	if (philo->name % 2)
		usleep(200);
	return (EXIT_SUCCESS);
}

void	routine(t_philo *philosopher, t_shared_data *data)
{
	if (sync_philos(philosopher) != EXIT_SUCCESS)
	{
		sem_post(data->sem_terminate);
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		put_action(philosopher, THINKING);
		grabneat(philosopher, data);
		put_action(philosopher, SLEEPING);
		my_sleep(data, data->variables[SLEEP_TIME]);
	}
}
