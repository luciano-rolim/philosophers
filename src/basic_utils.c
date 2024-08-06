/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:49:41 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/06 15:10:41 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
