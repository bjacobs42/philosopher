/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:34:44 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/31 18:15:42 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include "printing.h"

# define INIT_FAILURE 2
# define THREAD_FAILURE 3

typedef enum e_variable_index
{
	TTL_PHILOS,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	MUST_EAT
}			t_vari;

typedef struct s_shared_data
{
	t_log			*log;
	pthread_mutex_t	m_terminate;
	pthread_mutex_t	m_sync;
	struct timeval	start_tv;
	int				variables[5];
	bool			termination;
}				t_shared_data;

typedef struct s_philosophers
{
	pthread_t				thread;
	struct s_philosophers	*next;
	pthread_mutex_t			m_self;
	pthread_mutex_t			m_rfork;
	pthread_mutex_t			*m_lfork;
	t_shared_data			*data;
	long					last_meal;
	int						eat_times;
	int						name;
}				t_philo;

		/* print error functions */
void			put_error(char *s);
void			put_badin(char *s);
void			put_code(int err_code);
void			put_state(t_shared_data *data, int name, int state);

		/* main functions */
void			*routine(void *param);
void			*announcer(void *param);
void			add_queue(unsigned long ctime, int name, int type, t_log *log);
int				monitor(t_philo *philosophers, t_shared_data *data);

		/* misc functions */
int				parse(char **av);
int				ft_atoi(char *s);
bool			terminate(t_shared_data *data);
unsigned long	get_time(struct timeval start);
void			my_sleep(t_shared_data *data, unsigned long wait_time);

		/* clean up functions */
void			destroy(t_philo **philosophers);
void			clear_data(t_shared_data *data);
void			denouncer(t_log *log);

		/* initialization functions */
int				create_threads(t_philo *philosophers, t_shared_data *data);
t_philo			*init_philosophers(t_shared_data *data);
t_shared_data	*init_data(t_shared_data *data, char **av);

#endif
