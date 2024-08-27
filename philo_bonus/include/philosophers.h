/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:23:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/27 14:08:03 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
// # include <pthread.h>
# include <string.h>
# include <signal.h>
# include <time.h>
# include <semaphore.h>

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

typedef struct s_semaphores
{
	sem_t			counter;
	sem_t			printing;
	sem_t			*forks;
}	t_semaphores;

typedef struct s_prog
{
	t_params		params;
	t_semaphores	semaphores;
	t_philo			*philos;
	int				*philo_attribution;
	int				eat_ending_set;
	int				all_alive;
	int				no_deaths;
	int				wait_one_cicle;
	long int		strt_tm_micros;
	int				counter;
}	t_prog;

//Arg check functions
int			check_arguments(t_prog *prog, int argc, char **argv);
int			extra_checks(t_prog *prog);

//Cleaning functions
void		clean_prog(t_prog *prog, char *message);

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
int			semaphore_init(sem_t *semaphore, char *name);
// int			mutex_init(pthread_mutex_t *mutex);

//Start philos functions
int			calculus_wait_one_remaining(t_prog *prog, t_philo *philo);
int			start_position(t_prog *prog, t_philo *philo);
int			philo_variables_init(t_prog *prog, t_philo *philo);
int			calculus_time_to_think(t_prog *prog, t_philo *philo);

//Start variables functions
int			start_variables(t_prog *prog);

//Philo related processes
void		*death_process(t_prog *prog);
void		*philo_process(void *data);

//Other threads functions
void		*lone_philo(void *data);

//Thread utils functions
void		custom_write(t_philo *philo, char *message);

//Time functions
long int	timestamp(long int start_time, struct timeval tmp_time);
long int	time_in_microseconds(void);
long int	program_start_time(t_prog *prog);
void		delay_to_start(t_philo *philo);

#endif