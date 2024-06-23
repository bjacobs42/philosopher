/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 16:27:38 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/05/24 20:22:47 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H

# include <pthread.h>
# include <stdio.h>

# define USAGE "Usage: [philosophers_amount] [die_time] [eat_time]\
 [sleep_time] (optional)[must_eat]\n"
# define BAD_INPUT "Bad input: non-positve number/character: "

# define DIED_MSG "has died"
# define EAT_MSG "is eating"
# define THINK_MSG "is thinking"
# define SLEEP_MSG "is sleeping"
# define FORK_MSG "has taken a fork"

# define EXIT_FAILURE_MSG "ERROR: unknown\n"
# define INIT_FAILURE_MSG "ERROR: initialization failure\n"
# define FORK_FAILURE_MSG "ERROR: fork failure\n"
# define THREAD_FAILURE_MSG "ERROR: thread failure\n"
# define SEM_FAILURE_MSG "ERROR: semaphore failure\n"

typedef enum e_message
{
	DIED,
	EATING,
	THINKING,
	SLEEPING,
	TAKING_FORK
}				t_msg;

#endif
