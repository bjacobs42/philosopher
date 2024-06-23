/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: bjacobs <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 16:27:38 by bjacobs       #+#    #+#                 */
/*   Updated: 2023/05/31 17:25:34 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H

# include <pthread.h>

# define USAGE "Usage: [philosophers_amount] [die_time] [eat_time]\
 [sleep_time] (optional)[must_eat]\n"
# define BAD_INPUT "Bad input: non-positve number/character: "

# define DIED_MSG "died"
# define EAT_MSG "is eating"
# define THINK_MSG "is thinking"
# define SLEEP_MSG "is sleeping"
# define FORK_MSG "has taken a fork"

# define EXIT_FAILURE_MSG "ERROR: unknown\n"
# define INIT_FAILURE_MSG "ERROR: initialization failure\n"
# define THREAD_FAILURE_MSG "ERROR: thread failure\n"

typedef enum e_message
{
	DIED,
	EATING,
	THINKING,
	SLEEPING,
	TAKING_FORK
}				t_msg;

typedef struct s_message_data
{
	unsigned long	time_stamp;
	int				type;
	int				name;
}				t_msg_data;

typedef struct s_message_log
{
	pthread_t		thread;
	pthread_mutex_t	m_script;
	t_msg_data		*msg_lst;
	t_msg_data		*msg_queue;
	int				queue_size;
	int				lst_size;
	int				max_size;
}				t_log;

#endif
