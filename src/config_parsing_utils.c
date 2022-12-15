/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:16:46 by kwang             #+#    #+#             */
/*   Updated: 2022/12/15 16:15:06 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
str - string to be checked.

Description:
Iterates through str to check for non-whitespace characters i.e. \t,\v,\n,\r,' '
to identify if the current line is empty.

Return value:
Returns true if all characters are whitespace characters; false if not.
*/
int	is_str_empty(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (false);
	}
	return (true);
}

/*
Parameters:
str - string to be checked.

Description:
Iterates through str to check for characters only available to map. i.e.
1, 0, N, S, E, W. to identify if the current line belongs to a map element.

Return value:
Returns true if all characters are characters available to map; false otherwise
*/
int	is_str_map(const char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return (false);
	while (str[++i] != '\0')
	{
		if (ft_strchr(" \t\r\n\v01NSWE", str[i]) == NULL)
			return (false);
	}
	return (true);
}

/*
Parameters:
str - string to be checked.

Description:
Iterates through str to check for only digit characters in the string.

Return value:
Returns true if all characters are digits; false otherwise
*/
int	is_rgb_value(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}

/*
Parameters:
str - string to be checked.

Description:
Iterates through str to check if the values in the string are
values that would only be valid in the first line of the map.

Return value:
Returns true if it is not the first line of the map. False otherwise
*/
int	is_start_of_map(char *str)
{
	int	i;

	i = 0;
	if (!str || !ft_strlen(str))
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]) && str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_extra_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (0);
	return (1);
}
