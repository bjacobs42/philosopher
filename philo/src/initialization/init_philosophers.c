/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:19:13 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/31 17:18:30 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*new_philo(t_shared_data *data, int name)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (pthread_mutex_init(&philo->m_rfork, NULL) != 0)
		return (free(philo), NULL);
	if (pthread_mutex_init(&philo->m_self, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->m_rfork);
		return (free(philo), NULL);
	}
	philo->next = NULL;
	philo->data = data;
	philo->name = name;
	philo->last_meal = 0;
	philo->eat_times = 0;
	return (philo);
}

static void	add_philo(t_philo **philosophers, t_philo *philo)
{
	t_philo	*philosopher;

	if (!*philosophers)
		*philosophers = philo;
	else
	{
		philosopher = *philosophers;
		while (philosopher->next)
			philosopher = philosopher->next;
		philosopher->next = philo;
		philo->m_lfork = &philosopher->m_rfork;
	}
}

t_philo	*init_philosophers(t_shared_data *data)
{
	t_philo	*philosophers;
	t_philo	*philo;
	int		i;

	i = 0;
	philosophers = NULL;
	while (i < data->variables[TTL_PHILOS])
	{
		philo = new_philo(data, i + 1);
		if (!philo)
			return (destroy(&philosophers), NULL);
		add_philo(&philosophers, philo);
		i++;
	}
	add_philo(&philosophers, philosophers);
	if (!philosophers)
		clear_data(data);
	return (philosophers);
}
