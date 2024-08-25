/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:23:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/25 12:05:50 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <signal.h>
# include <time.h>

typedef struct s_philo
{
	int				nbr;
	struct timeval	tmp_time;
	pthread_mutex_t	*grab_first;
	pthread_mutex_t	*grab_second;
	int				start_position;
	int				wait_one_remaining;
	int				max_wait_one_remaining;
	int				must_eat;
	long int		last_meal;
	int				even_prog;
	void			*prog;
	long int		strt_tm;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	long int		time_to_double_think;
	int				*all_alive;
	int				eat_ending_set;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t *mutex_all_alive;
	pthread_mutex_t *mutex_print;
}	t_philo;

typedef struct s_params
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_must_eat;		
}	t_params;

typedef struct s_mutexes
{
	pthread_mutex_t printing;
	pthread_mutex_t	all_alive;
	pthread_mutex_t	forks[250];
}	t_mutexes;

typedef struct s_prog
{
	t_params		params;
	t_mutexes		mutexes;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_t		death_checker;
	int				eat_ending_set;
	int				all_alive;
	int				wait_one_cicle;
	long int		strt_tm;
}	t_prog;

//Arg check functions
int			check_arguments(t_prog *prog, int argc, char **argv);
int			extra_checks(t_prog *prog);

//Basic Utils functions
int			string_len(char *s);
int			char_cmp(char *s1, char *s2);

//Cleaning functions
void		clean_prog(t_prog *prog, char *message);

//Num functions	return ();
long int	custom_atol(char *str_number);
int			is_even(int nbr);
int			ft_bigger(int a, int b);
int			ft_lower(int a, int b);
int			is_num_digit(char c);

//Program utils
int			param_attribution(t_prog *prog, int nbr, int arg);
int			print_error(char *message);
void		*print_error_pointer(char *message);
void		*ft_calloc(size_t nmemb, size_t size);
int			mutex_init(pthread_mutex_t *mutex);

//Start variables functions
int			start_variables(t_prog *prog);

//Thread functions
void		*philo_thread(void *data);
void		*death_thread(void *data);
void		*lone_philo_thread(void *data);

//Time functions
long int	time_mls(void);
long int	simulation_timestamp(long int start_time, struct timeval tmp_time);
void		delay_to_start(t_philo *philo);

#endif