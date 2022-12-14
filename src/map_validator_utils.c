/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:16:27 by kwang             #+#    #+#             */
/*   Updated: 2022/12/14 16:37:14 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
temp_arr - An empty 2D array
arrlen - The length of temp_arr
size - Size of the array that is going to be filled up with spaces
Description:
This function will take in an empty 2D array and memory allocate
each character pointer by the size of 'size + 2'. It will be terminated
with a newline character followed by nul terminator.
The remaining bytes will be filled with the space character
Return value:
Does not return anything
*/
void	fill_space(char **temp_arr, int arrlen, int size)
{
	int	i;

	i = 0;
	while (i < arrlen)
	{
		temp_arr[i] = malloc(sizeof(char) * (size + 1));
		temp_arr[i][size] = '\0';
		ft_memset(temp_arr[i], ' ', size);
		i++;
	}
}

/*
Parameters:
dst - The destination 2D array
src - The source 2D array
Description:
It will copy all characters from src into dst string by string.
It will not nul terminate the string afterit finishes copying.
Return value:
Does not return anything
*/
void	copy_into_temp(char **dst, char **src, int len)
{
	int		i;
	int		arrlen;

	arrlen = ft_2darrlen(src);
	i = 0;
	while (i < arrlen)
	{
		ft_memcpy(dst[i], src[i], len);
		i++;
	}
}

/*
Parameters:
config_cache - The 2D map array stored in the stack

Description:
The function continuously iterates through each line in the
2D array and find the longest line.

Return value:
Returns the length of the longest line.
*/
int	get_longest_line(char **config_cache)
{
	int	max;
	int	i;
	int	arrlen;

	i = 0;
	max = 0;
	arrlen = ft_2darrlen(config_cache);
	while (i < arrlen)
	{
		if ((int)ft_strlen(config_cache[i]) > max)
			max = ft_strlen(config_cache[i]);
		i++;
	}
	return (max);
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
int	check_empty_lines(char **temp)
{
	int	i;

	i = 0;
	while (temp[i] != NULL)
	{
		if (is_str_empty(temp[i]))
			return (true);
		i++;
	}
	return (false);
}
