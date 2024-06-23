/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:19:13 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/31 17:32:24 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*new_philo(t_shared_data *data, int name)
{
	t_philo	*philo;
	char	*str_name;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	str_name = ft_itoa(name);
	if (!str_name)
		return (free(philo), NULL);
	philo->name_self = ft_strjoin("sem-philo-", 0, str_name);
	free(str_name);
	if (!philo->name_self)
		return (free(philo), NULL);
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
	}
}

t_philo	*init_philosophers(t_shared_data *data)
{
	t_philo	*philosophers;
	t_philo	*philo;
	size_t	i;

	i = 0;
	philosophers = NULL;
	while (i < (size_t)data->variables[TTL_PHILOS])
	{
		philo = new_philo(data, i + 1);
		if (!philo)
			return (destroy(&philosophers, data), NULL);
		add_philo(&philosophers, philo);
		i++;
	}
	add_philo(&philosophers, philosophers);
	if (!philosophers)
		clear_data(data);
	return (philosophers);
}
