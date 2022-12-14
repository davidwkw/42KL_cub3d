/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:16:04 by kwang             #+#    #+#             */
/*   Updated: 2022/12/14 14:26:27 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_forw_back(t_player *p, t_map map, int dir)
{
	double	move_speed;

	move_speed = 1.0 / GRID_SIZE * MOVE_MULTIPLE;
	if (dir == FORWARD)
	{
		if (map.map[(int)(p->py + p->dir_v.y * move_speed)][(int)p->px] != '1')
			p->py += p->dir_v.y * move_speed;
		if (map.map[(int)p->py][(int)(p->px + p->dir_v.x * move_speed)] != '1')
			p->px += p->dir_v.x * move_speed;
	}
	else if (dir == BACKWARD)
	{
		if (map.map[(int)(p->py - p->dir_v.y * move_speed)][(int)p->px] != '1')
			p->py -= p->dir_v.y * move_speed;
		if (map.map[(int)p->py][(int)(p->px - p->dir_v.x * move_speed)] != '1')
			p->px -= p->dir_v.x * move_speed;
	}
}

void	handle_left_right(t_player *p, t_map map, int dir)
{
	if (dir == RIGHT)
		handle_rotation(p, M_PI / 2);
	else if (dir == LEFT)
		handle_rotation(p, -(M_PI / 2));
	handle_forw_back(p, map, FORWARD);
	if (dir == RIGHT)
		handle_rotation(p, -(M_PI / 2));
	else if (dir == LEFT)
		handle_rotation(p, M_PI / 2);
}

void	handle_rotation(t_player *p, double rot_speed)
{
	double	prev_dir_x;
	double	prev_plane_x;

	prev_dir_x = p->dir_v.x;
	p->dir_v.x = p->dir_v.x * cos(rot_speed)
		- p->dir_v.y * sin(rot_speed);
	p->dir_v.y = prev_dir_x * sin(rot_speed)
		+ p->dir_v.y * cos(rot_speed);
	prev_plane_x = p->cam_vect.x;
	p->cam_vect.x = p->cam_vect.x * cos(rot_speed)
		- p->cam_vect.y * sin(rot_speed);
	p->cam_vect.y = prev_plane_x * sin(rot_speed)
		+ p->cam_vect.y * cos(rot_speed);
}
