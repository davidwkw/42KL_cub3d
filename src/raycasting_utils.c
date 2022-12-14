/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:15:59 by kwang             #+#    #+#             */
/*   Updated: 2022/12/14 14:26:31 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_delta(t_ray_vars *ray_vars)
{
	if (ray_vars->ray_dir.x == 0)
		ray_vars->delta_x = 1e30;
	else
		ray_vars->delta_x = absolute_double(1 / ray_vars->ray_dir.x);
	if (ray_vars->ray_dir.y == 0)
		ray_vars->delta_y = 1e30;
	else
		ray_vars->delta_y = absolute_double(1 / ray_vars->ray_dir.y);
}

void	calc_side_dist(t_ray_vars *ray_vars, t_player p)
{
	if (ray_vars->ray_dir.x < 0)
	{
		ray_vars->step_x = -1;
		ray_vars->side_x = (p.px - ray_vars->map_x) * ray_vars->delta_x;
	}
	else
	{
		ray_vars->step_x = 1;
		ray_vars->side_x = (ray_vars->map_x + 1.0 - p.px) * ray_vars->delta_x;
	}
	if (ray_vars->ray_dir.y < 0)
	{
		ray_vars->step_y = -1;
		ray_vars->side_y = (p.py - ray_vars->map_y) * ray_vars->delta_y;
	}
	else
	{
		ray_vars->step_y = 1;
		ray_vars->side_y = (ray_vars->map_y + 1.0 - p.py) * ray_vars->delta_y;
	}
}

int	determine_side_hit(t_ray_vars ray_vars)
{
	if (ray_vars.side == 0)
	{
		if (ray_vars.ray_dir.x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray_vars.ray_dir.y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

void	perform_dda(t_ray_vars *ray_vars, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray_vars->side_x < ray_vars->side_y)
		{
			ray_vars->side_x += ray_vars->delta_x;
			ray_vars->map_x += ray_vars->step_x;
			ray_vars->side = 0;
		}
		else
		{
			ray_vars->side_y += ray_vars->delta_y;
			ray_vars->map_y += ray_vars->step_y;
			ray_vars->side = 1;
		}
		if (map[ray_vars->map_y][ray_vars->map_x] == '1')
			hit = 1;
	}
	if (ray_vars->side == 0)
		ray_vars->perp_wall_dist = ray_vars->side_x - ray_vars->delta_x;
	else
		ray_vars->perp_wall_dist = ray_vars->side_y - ray_vars->delta_y;
}
