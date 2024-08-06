/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:23:09 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 12:46:57 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// # define ULONG_MAX_STR "18446744073709551615"
// # define LONG_MAX_STR1 "9223372036854775807"
// # define INT_MAX_STR "2147483647"

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
	int		index;
	int		index_next;
	int		eat_count;
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
	pthread_mutex_t *change_priority_count;
	pthread_mutex_t	*forks;
	int				*bool_forks;
}	t_mutexes;

typedef struct s_prog
{
	t_params		params;
	t_mutexes		mutexes;
	pthread_t		*threads;
	t_philo			*philos;
	int				all_alive;
	int				priority_line_count;
	long int		start_time;
}	t_prog;

//Check functions
int		check_arguments(t_prog *prog, int argc, char **argv);

//Struct Utils functions
int			philo_struct(t_prog *prog, int nbr, int arg);
long int	get_time_mls(void);
int			struct_malloc(t_prog *prog);

//Basic Utils functions
int			is_num_digit(char c);
int			string_len(char *s);
int			char_cmp(char *s1, char *s2);
long int	custom_atol(char *str_number);
int			is_even(int nbr);
int			print_error(char *message);
void		*custom_calloc(size_t nmemb, size_t size);

//Cleaning functions
void		clean_prog(t_prog *prog, char *message);

#endif