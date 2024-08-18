/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:23:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/17 15:12:48 by lmeneghe         ###   ########.fr       */
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
	int		nbr;
	// int		prev;
	// int		next;
	int		index;
	int		index_next;
	// int		*bool_1;
	// int		*bool_2;
	int		grab_first;
	int		grab_second;
	// int		eat_first_priority;
	int		start_position;
	int		wait_one_remaining;
	int		max_wait_one_remaining;
	int		eat_count;
	int		must_eat;
	// int		is_thinking;
	// int		on_queue;
	int		even_prog;
	void	*prog;
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
	pthread_mutex_t *fork_availability;
	pthread_mutex_t *eat_first_count;
	pthread_mutex_t *printing;
	pthread_mutex_t	*queue;
	pthread_mutex_t	*forks;
	int				*bool_forks;
}	t_mutexes;

typedef struct s_queue
{
	int	*arr;
	int	arr_last;
	int	beggining;
	int	ending;
	int	size;
}	t_queue ;

typedef struct s_prog
{
	t_params		params;
	t_mutexes		mutexes;
	pthread_t		*threads;
	t_philo			*philos;
	t_queue			queue;
	int				all_alive;
	// int				eat_first_line;
	int				even_philos;
	int				wait_one_cicle;
	long int		strt_tm;
}	t_prog;

//Arg check functions
int			check_arguments(t_prog *prog, int argc, char **argv);

//Basic Utils functions
int			string_len(char *s);
int			char_cmp(char *s1, char *s2);

//Cleaning functions
void		clean_prog(t_prog *prog, char *message);

//Num functions
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
// int			eat_first_priority(t_prog *prog, t_philo *philo);

//Queue functions
int			add_to_queue(t_prog *prog, t_philo *philo);
int			remove_from_queue(t_prog *prog, t_philo *philo);

//Start variables functions
int			start_variables(t_prog *prog);

//Thread functions
void		*philo_thread(void *data);

//Time functions
long int	time_mls(void);
long int	timestamp(t_prog *prog);

#endif