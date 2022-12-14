/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:07:05 by kwang             #+#    #+#             */
/*   Updated: 2022/12/14 12:44:30 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
Parameters:
assets - data structure to be checked if data members are unpopulated.

Description:
Iterates through t_assets data structure and evaluate is any variable is set
to NULL; 

Return value:
Returns true if all variables have a non-NULL value; false otherwise.
*/
int	check_assets_set(const t_assets assets)
{
	size_t	i;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		if (assets.textures[i] == NULL)
			return (false);
		++i;
	}
	i = 0;
	while (i < COLOURS_SIZE)
	{
		if (assets.colours[i] == NULL)
			return (false);
		++i;
	}
	return (true);
}
