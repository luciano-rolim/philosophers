/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:10:40 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/08/29 10:14:46 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

char	*itoa_extra(char *str, int start, int end, char tmp)
{
	while (start < end)
	{
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;
		start++;
		end--;
	}
	return (str);
}

char	*custom_itoa(int num)
{
	int		start;
	int		i;	
	int		end;
	char	tmp;
	char	*str;

	i = 0;
	str = (NULL);
	str = malloc(MAX_INT_LENGHT);
	if (!str)
		return (NULL);
	while (num > 0)
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	}
	str[i] = '\0';
	start = 0;
	end = i - 1;
	str = itoa_extra(str, start, end, tmp);
	return (str);
}
