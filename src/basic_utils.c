/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:49:41 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/05 19:34:13 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

int	char_cmp(char *s1, char *s2)
{
	long int	i;
	int			result;

	if (!s1 || !s2)
		return (0);
	i = 0;
	result = 0;
	while ((s1[i] || s2[i]))
	{
		result = ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (result != 0)
			return (result);
		i++;
	}
	return (result);
}

long int custom_atol(char *str_number)
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

int	print_error(char *message)
{
	if (!message)
		return (0);
	printf("%s", message);
	return (0);
}

void	*custom_calloc(size_t nmemb, size_t size)
{
	size_t	full_size;
	size_t	i;
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	full_size = nmemb * size;
	if (full_size / size != nmemb)
		return (NULL);
	ptr = malloc(full_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < full_size)
		((unsigned char *)ptr)[i++] = 0;
	return (ptr);
}
