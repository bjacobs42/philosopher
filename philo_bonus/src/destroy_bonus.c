/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:10:10 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/31 21:38:12 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_data(t_shared_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i++ < data->variables[TTL_PHILOS])
		sem_post(data->sem_ate);
	sem_close(data->sem_print);
	sem_close(data->sem_terminate);
	sem_close(data->sem_forks);
	sem_close(data->sem_sync);
	sem_close(data->sem_ate);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_TERM);
	sem_unlink(SEM_SYNC);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_ATE);
}

void	destroy(t_philo **philosophers, t_shared_data *data)
{
	t_philo			*tmp;

	clear_data(data);
	while (*philosophers && data->variables[TTL_PHILOS]--)
	{
		tmp = (*philosophers)->next;
		sem_unlink((*philosophers)->name_self);
		free((*philosophers)->name_self);
		free(*philosophers);
		*philosophers = tmp;
	}
}
