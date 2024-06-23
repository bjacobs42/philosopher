/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:12:10 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/24 20:38:12 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_philo			*philosophers;
	t_shared_data	data;

	if (ac < 5 || ac > 6)
		return (put_error(USAGE), EXIT_FAILURE);
	if (parse(av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!init_data(&data, av))
		return (put_error(INIT_FAILURE_MSG), INIT_FAILURE);
	philosophers = init_philosophers(&data);
	if (!philosophers)
		return (put_error(INIT_FAILURE_MSG), INIT_FAILURE);
	if (create_procs(philosophers, &data) != EXIT_SUCCESS)
	{
		destroy(&philosophers, &data);
		return (put_error(FORK_FAILURE_MSG), FORK_FAILURE);
	}
	monitor(philosophers, &data);
	destroy(&philosophers, &data);
	return (EXIT_SUCCESS);
}
