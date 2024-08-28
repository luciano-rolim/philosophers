/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:23:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 14:34:29 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <signal.h>
# include <time.h>
# include <semaphore.h>
# include <fcntl.h>

# define  SEM_FORK_NAME "/sem_fork"
# define  SEM_PRINT_NAME "/sem_print"

typedef struct s_philo
{
	int				nbr;
	struct timeval	tmp_time;
	int				start_position;
	int				wait_one_remaining;
	int				max_wait_one_remaining;
	int				must_eat;
	long int		last_meal;
	int				even_prog;
	void			*prog;
	long int		strt_tm_micros;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	long int		time_to_double_think;
	int				*all_alive;
	int				eat_ending_set;
	char			*sem_name_last_meal;
	sem_t			*sem_last_meal;
}	t_philo;

typedef struct s_params
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_must_eat;
	int				time_to_die_mls;	
}	t_params;

typedef struct s_sems
{
	sem_t			*forks;
	sem_t			*printing;
}	t_sems;

typedef struct s_prog
{
	t_params		params;
	t_sems			sems;
	pthread_t		*threads;
	t_philo			philo;
	pthread_t		death_checker;
	int				eat_ending_set;
	int				all_alive;
	int				wait_one_cicle;
	long int		strt_tm_micros;
}	t_prog;

//Arg check functions
int			check_arguments(t_prog *prog, int argc, char **argv);
int			extra_checks(t_prog *prog);

//Cleaning functions
void		clean_prog(t_prog *prog, char *message);
void		unlink_sems(void);

//Num functions	return
long int	custom_atol(char *str_number);
int			is_even(int nbr);
int			is_num_digit(char c);
int			string_len(char *s);

//Program utils
int			param_attribution(t_prog *prog, int nbr, int arg);
int			print_error(char *message);
void		*print_error_pointer(char *message);
void		*ft_calloc(size_t nmemb, size_t size);

//Start philos functions
int			calculus_wait_one_remaining(t_prog *prog, t_philo *philo);
int			start_position(t_prog *prog, t_philo *philo);
// int			grab_fork_order(t_prog *prog, t_philo *philo, int i);
int			philo_variables_init(t_prog *prog, t_philo *philo, int i);
int			calculus_time_to_think(t_prog *prog, t_philo *philo);

//Start variables functions
int			start_variables(t_prog *prog);

//Philo thread functions
void		*philo_process(t_prog *prog, int i);
void		*death_thread(void *data);

//Other threads functions
void		*lone_philo(t_prog *prog, int i);

//Thread utils functions
void		custom_write(t_philo *philo, char *message, t_prog *prog);

//Time functions
long int	timestamp(long int start_time, struct timeval tmp_time);
long int	time_in_microseconds(void);
long int	program_start_time(t_prog *prog);
void		delay_to_start(t_philo *philo);

//bonus stuff
char*		custom_itoa(int num);
int			exit_gracefully(t_prog *prog, t_philo *philo);
int			init_thread(pthread_t *thread, void *(*func) (void *), void *data);
void		children_open_sems(t_prog *prog, t_philo *philo);
void		children_close_sems(t_prog *prog, t_philo *philo);
int			philo_init(t_prog *prog, t_philo *philo, int i);

#endif