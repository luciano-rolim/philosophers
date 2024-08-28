/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:05:55 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/28 15:37:03 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	param_attribution(t_prog *prog, int nbr, int arg)
{
	if (!prog || (arg < 1 || arg > 5))
		return (0);
	if (arg == 1)
		prog->params.nbr_philos = nbr;
	else if (arg == 2)
	{
		prog->params.time_to_die = (nbr * 1000);
		prog->params.time_to_die_mls = nbr;
	}
	else if (arg == 3)
		prog->params.time_to_eat = (nbr * 1000);
	else if (arg == 4)
		prog->params.time_to_sleep = (nbr * 1000);
	else if (arg == 5)
		prog->params.nbr_must_eat = nbr;
	return (1);
}

int	print_error(char *message)
{
	if (!message)
		return (0);
	printf("%s", message);
	return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *prefix, char const *suffix)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!prefix || !suffix)
		return (NULL);
	size = ft_strlen(prefix) + ft_strlen(suffix) + 1;
	new_str = malloc(size);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (prefix[i])
	{
		new_str[i] = prefix[i];
		i++;
	}
	j = 0;
	while (suffix[j])
	{
		new_str[i + j] = suffix[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}
