/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:02:42 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/29 10:11:03 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	custom_atol(char *str_number)
{
	int			i;
	long int	nbr;

	if (!str_number)
		return (-1);
	i = 0;
	nbr = 0;
	while (str_number[i])
	{
		if (!is_num_digit(str_number[i]))
			return (-1);
		nbr = nbr * 10 + str_number[i] - '0';
		i++;
	}
	return (nbr);
}

int	is_even(int nbr)
{
	if (nbr % 2 == 0)
		return (1);
	else
		return (0);
}

int	is_num_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	string_len(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
