#include "cub3d.h"

static void draw_ver_line(t_data *scrn_data, int x, int start, int end, int color)
{
	int *scrn;

	scrn = (int *)scrn_data->addr;
	while (start != end)
	{
		scrn[start * scrn_data->size_line / (scrn_data->bpp / 8) + x] = color;
		++start;
	}
}

static void	calc_delta(t_ray_vars *ray_vars)
{
	if (ray_vars->ray_dir.x == 0)
		ray_vars->delta_x = 1e30;
	else
		ray_vars->delta_x = absolute_double(1/ray_vars->ray_dir.x);
	if (ray_vars->ray_dir.y == 0)
		ray_vars->delta_y = 1e30;
	else
		ray_vars->delta_y = absolute_double(1/ray_vars->ray_dir.y);
}

static void	calc_side_dist(t_ray_vars *ray_vars, t_player p)
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

static int	determine_side_hit(t_ray_vars ray_vars)
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

static void	perform_dda(t_ray_vars *ray_vars, char **map)
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
	return line_vars;
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
	return tex_x;
}

void draw_textured_line(t_ray_vars ray_vars, t_player p,
						t_data tex_data, t_data *scrn_buff)
{
	t_line_vars	line_vars;
	int			tex_x;
	int			tex_y;
	double		step;
	double		texture_pos;
	int			y;
	int			pixel;
	int			*scrn;
	int			*tex;

	scrn = (int *)scrn_buff->addr;
	tex = (int *)tex_data.addr; 
	line_vars = calc_line_vals(ray_vars);
	tex_x = calc_texture_x(ray_vars, p, tex_data.width);
	step = 1.0 * tex_data.height / line_vars.line_height;
	texture_pos = (line_vars.line_start
				- WIN_HEIGHT / 2 + line_vars.line_height / 2) * step;
	y = line_vars.line_start;
	while (y < line_vars.line_end)
	{
		tex_y = (int)texture_pos & (tex_data.height - 1);
		texture_pos += step;
		pixel = tex[tex_y * tex_data.size_line / (tex_data.bpp / 8) + tex_x];
		scrn[y * scrn_buff->size_line / (scrn_buff->bpp / 8) + ray_vars.scrn_x] = pixel;
		++y;
	}
}

void	print_ray(t_ray_vars ray_vars)
{
	printf("ray x %f\n", ray_vars.ray_dir.x);
	printf("ray y %f\n", ray_vars.ray_dir.y);
	printf("dx %f\n", ray_vars.delta_x);
	printf("dy %f\n", ray_vars.delta_y);
	printf("sx %f\n", ray_vars.side_x);
	printf("sy %f\n", ray_vars.side_y);
}

void	perform_raycast(t_cache tex_cache, t_player p,
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
		ray_vars.ray_dir = add_vectors(p.dir_vect,
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
