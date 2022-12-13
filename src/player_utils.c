/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:16:01 by kwang             #+#    #+#             */
/*   Updated: 2022/12/13 18:48:14 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to refactor so that it takes into account player vector x/y rather than char.
static void	set_camera_plane(char dir, t_vector *cam_vect, double fov)
{
	fov /= 2;
	if (dir == 'E')
	{	
		cam_vect->x = 0;
		cam_vect->y = tan(fov / 180.0 * M_PI);
	}
	else if (dir == 'N')
	{
		cam_vect->x = tan(fov / 180.0 * M_PI);
		cam_vect->y = 0;
	}
	else if (dir == 'W')
	{
		cam_vect->x = 0;
		cam_vect->y = -tan(fov / 180.0 * M_PI);
	}
	else if (dir == 'S')
	{
		cam_vect->x = -tan(fov / 180.0 * M_PI);
		cam_vect->y = 0;
	}
}

static void	set_player_dir_vect(char dir, t_vector *p_vector)
{
	if (dir == 'E')
	{	
		p_vector->x = 1;
		p_vector->y = 0;
	}
	else if (dir == 'N')
	{
		p_vector->x = 0;
		p_vector->y = -1;
	}
	else if (dir == 'W')
	{
		p_vector->x = -1;
		p_vector->y = 0;
	}
	else if (dir == 'S')
	{
		p_vector->x = 0;
		p_vector->y = 1;
	}
}

/*
Parameters:
player - Address of player structure to initialize
oritentation - player orientation in map
x - x coordinate of player
y - y coordinate of player 

Description:
Sets the player's coordinates, angle and delta x and y repectively.

Return value:
Returns nothing.
*/
void	init_player_var(t_player *player, char orientation, int x, int y)
{
	player->px = x + 0.5;
	player->py = y + 0.5;
	set_player_dir_vect(orientation, &player->dir_v);
	set_camera_plane(orientation, &player->cam_vect, FOV);
}

/*
Parameters:
key - Keycode of button pressed
player - player structure containing player coordinates and player's dx and dy

Description:
Handles WASD movement keys on mac and linux for player movement

Return value:
Returns nothing.
*/
void	handle_player_movement(int key, t_player *p, t_map map)
{
	if (ft_strchr("ws", key) != 0 || key == 13 || key == 1)
	{
		if (key == 'w' || key == 13)
			handle_forw_back(p, map, FORWARD);
		else if (key == 's' || key == 1)
			handle_forw_back(p, map, BACKWARD);
	}
	if (ft_strchr("ad", key) != 0 || key == 2 || key == 0)
	{
		if (key == 'a' || key == 0)
			handle_left_right(p, map, LEFT);
		else if (key == 'd' || key == 2)
			handle_left_right(p, map, RIGHT);
	}
}

void	handle_arrow_rotate(int key, t_player *p)
{
	if (key == 123 || key == 65361)
		handle_rotation(p, -RAD * ARROW_ROT_MULTIPLE);
	if (key == 124 || key == 65363)
		handle_rotation(p, RAD * ARROW_ROT_MULTIPLE);
}
