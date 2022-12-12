/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:07:29 by kwang             #+#    #+#             */
/*   Updated: 2022/12/12 16:46:50 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line_vars	calc_line_vals(t_ray_vars ray_vars)
{
	t_line_vars	line_vars;

	line_vars = (t_line_vars){};
	line_vars.line_height = (int)(WIN_HEIGHT / ray_vars.perp_wall_dist);
	line_vars.line_start = -line_vars.line_height / 2 + WIN_HEIGHT / 2;
	if (line_vars.line_start < 0)
		line_vars.line_start = 0;
	line_vars.line_end = line_vars.line_height / 2 + WIN_HEIGHT / 2;
	if (line_vars.line_end >= WIN_HEIGHT)
		line_vars.line_end = WIN_HEIGHT - 1;
	return (line_vars);
}

int	calc_texture_x(t_ray_vars ray_vars, t_player p, int tex_width)
{
	double	wall_x;
	int		tex_x;

	if (ray_vars.side == 0)
		wall_x = p.py + ray_vars.perp_wall_dist * ray_vars.ray_dir.y;
	else
		wall_x = p.px + ray_vars.perp_wall_dist * ray_vars.ray_dir.x;
	wall_x -= floorf((wall_x));
	tex_x = (int)(wall_x * (double)tex_width);
	if (ray_vars.side == 0 && ray_vars.ray_dir.x > 0)
		tex_x = tex_width - tex_x - 1;
	if (ray_vars.side == 1 && ray_vars.ray_dir.y < 0)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	draw_textured_line(t_ray_vars ray_v, t_player p,
						t_data tex_data, t_data *s_buff)
{
	t_line_vars	line_vars;
	t_tex		tex;
	int			y;
	int			*scrn_addr;
	int			*tex_addr;

	scrn_addr = (int *)s_buff->addr;
	tex_addr = (int *)tex_data.addr;
	line_vars = calc_line_vals(ray_v);
	tex.tex_x = calc_texture_x(ray_v, p, tex_data.width);
	tex.step = 1.0 * tex_data.height / line_vars.line_height;
	tex.texture_pos = (line_vars.line_start
			- WIN_HEIGHT / 2 + line_vars.line_height / 2) * tex.step;
	y = line_vars.line_start - 1;
	while (++y < line_vars.line_end)
	{
		tex.tex_y = (int)tex.texture_pos & (tex_data.height - 1);
		tex.texture_pos += tex.step;
		scrn[y * s_buff->size_line / (s_buff->bpp / 8) + ray_v.scrn_x]
			= tex_addr[tex.tex_y * tex_data.size_line / (tex_data.bpp / 8)
			+ tex.tex_x];
	}
}

void	render_view(t_cache tex_cache, t_player p,
						char **map, t_data *scrn_buff)
{
	double		cam_plane_pos_x;
	t_ray_vars	ray_vars;
	int			texture;

	cam_plane_pos_x = 0.0f;
	ray_vars = (t_ray_vars){};
	while (ray_vars.scrn_x < WIN_WIDTH)
	{
		cam_plane_pos_x = 2 * ray_vars.scrn_x / (double)WIN_WIDTH - 1;
		ray_vars.ray_dir = add_vectors(p.dir_v,
				multiply_vector(p.cam_vect, cam_plane_pos_x));
		ray_vars.map_x = (int)p.px;
		ray_vars.map_y = (int)p.py;
		calc_delta(&ray_vars);
		calc_side_dist(&ray_vars, p);
		perform_dda(&ray_vars, map);
		texture = determine_side_hit(ray_vars);
		draw_textured_line(ray_vars, p, tex_cache.textures[texture], scrn_buff);
		++ray_vars.scrn_x;
	}
}
