/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:42:52 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/26 11:31:02 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static char	*check_plus_and_zero(char *number)
{
	int	i;
	int	non_zero;

	if (!number)
		return (NULL);
	i = 0;
	non_zero = 0;
	if (number[0] == '+')
	{
		number++;
		if (!number[i])
			return (NULL);
		while (number[i])
		{
			if (number[i++] != '0')
				non_zero = 1;
		}
		if (non_zero == 0)
			return (NULL);
	}
	while ((*number == '0') && ((*number + 1) != '\0'))
		number++;
	return (number);
}

static int	process_arg(t_prog *prog, char *str_number, int arg)
{
	long int	nbr;

	if (!str_number || string_len(str_number) == 0)
		return (0);
	str_number = check_plus_and_zero(str_number);
	if (!str_number)
		return (0);
	if (string_len(str_number) > 10)
		return (0);
	nbr = custom_atol(str_number);
	if (nbr > INT_MAX || nbr < 0)
		return (0);
	if (!param_attribution(prog, nbr, arg))
		return (0);
	return (1);
}

static int	first_check(int argc, char **argv, int *n_to_check)
{
	if (!n_to_check)
		return (0);
	if (!argv)
		return (print_error("Error: argv pointer is NULL\n"));
	if (argc == 6)
		(*n_to_check) = 5;
	else if (argc == 5)
		(*n_to_check) = 4;
	else
		return (print_error("Error: invalid number of arguments\n"));
	return (1);
}

static int	initialize_variables(t_prog *prog)
{
	if (!prog)
		return (print_error("Error on initialize variables call\n"));
	prog->all_alive = 1;
	prog->strt_tm = -1;
	prog->wait_one_cicle = -1;
	prog->eat_ending_set = -1;
	prog->strt_tm = -1;
	prog->params.nbr_philos = -1;
	prog->params.time_to_die = -1;
	prog->params.time_to_eat = -1;
	prog->params.time_to_sleep = -1;
	prog->params.nbr_must_eat = -1;
	return (1);
}

int	check_arguments(t_prog *prog, int argc, char **argv)
{
	int		i;
	int		n_to_check;
	char	*tmp_message;

	n_to_check = 0;
	if (!first_check(argc, argv, &n_to_check))
		return (0);
	if (!initialize_variables(prog))
		return (0);
	i = 1;
	while (i <= n_to_check)
	{
		if (!argv[i])
		{
			printf("Error: Index %i of argv array is NULL\n", i);
			return (0);
		}
		if (!process_arg(prog, argv[i], i))
		{
			tmp_message = "Insert a valid number between 0 and INT_MAX.";
			printf("Error: index %i is not valid. %s\n", i, tmp_message);
			return (0);
		}
		i++;
	}
	return (1);
}
