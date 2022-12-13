/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:16:46 by kwang             #+#    #+#             */
/*   Updated: 2022/12/13 18:55:36 by kwang            ###   ########.fr       */
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
