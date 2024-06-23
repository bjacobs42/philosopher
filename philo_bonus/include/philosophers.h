/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:34:44 by bjacobs           #+#    #+#             */
/*   Updated: 2023/05/25 16:39:31 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include "printing.h"

# define SEM_ATE "sem-philo-ate"
# define SEM_SYNC "sem-philo-sync"
# define SEM_TERM "sem-philo-terminate"
# define SEM_FORK "sem-philo-forks"
# define SEM_PRINT "sem-philo-printing"
# define SEM_DYING "sem-philo-dying"

enum e_error_codes
{
	INIT_FAILURE = 2,
	FORK_FAILURE = 3,
	THREAD_FAILURE = 4
};

enum e_variable_index
{
	TTL_PHILOS,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	MUST_EAT
};

typedef struct s_shared_data
{
	sem_t			*sem_terminate;
	sem_t			*sem_print;
	sem_t			*sem_forks;
	sem_t			*sem_ate;
	sem_t			*sem_sync;
	struct timeval	start_tv;
	int				variables[5];
}				t_shared_data;

typedef struct s_philosopher
{
	struct s_philosopher	*next;
	t_shared_data			*data;
	sem_t					*sem_self;
	char					*name_self;
	unsigned long			last_meal;
	int						eat_times;
	int						name;
	int						pid;
}				t_philo;

		/* print error functions */
void			put_error(char *s);
void			put_badin(char *s);
void			put_code(int err_code);
void			put_state(t_shared_data *data, int name, int state);

		/* main functions */
void			routine(t_philo *philosopher, t_shared_data *data);
int				monitor(t_philo *philosophers, t_shared_data *data);

		/* misc functions */
int				parse(char **av);
int				ft_atoi(char *s);
char			*ft_itoa(int num);
char			*ft_strjoin(char *s1, char c, char *s2);
bool			terminate(t_shared_data *data);
unsigned long	get_time(struct timeval start);
void			my_sleep(t_shared_data *data, unsigned long wait_time);

		/* clean up functions */
void			destroy(t_philo **philosophers, t_shared_data *data);
void			clear_data(t_shared_data *data);

		/* initialization functions */
int				create_procs(t_philo *philosophers, t_shared_data *data);
t_philo			*init_philosophers(t_shared_data *data);
t_shared_data	*init_data(t_shared_data *data, char **av);

#endif
