/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/12/12 17:37:36 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_minimap(t_data *minimap_buff, t_cache cache, t_player p)
{
	const int	minimap_size = WIN_HEIGHT / MINIMAP_SCALE;
	const int	minimap_grid_size = minimap_size / MINIMAP_GRID_SCALE;
	const int	minimap_plyr_size = minimap_size / MINIMAP_PLYR_SCALE;

	copy_img(minimap_buff, &cache.minimap,
		(minimap_size / 2 - p.px * minimap_grid_size),
		(minimap_size / 2 - p.py * minimap_grid_size));
	copy_img(minimap_buff, &cache.minimap_player,
		minimap_buff->width / 2 - minimap_plyr_size / 2,
		minimap_buff->height / 2 - minimap_plyr_size / 2);
}

void	render_minimap(t_vars *vars)
{
	t_data		minimap_buffer;
	const int	minimap_size = WIN_HEIGHT / MINIMAP_SCALE;

	create_image(vars->mlx, &minimap_buffer, minimap_size, minimap_size);
	fill_image_with_color((int *)minimap_buffer.addr,
		minimap_buffer.width * minimap_buffer.height, T70_BLUE);
	paint_minimap(&minimap_buffer, vars->texture_cache, vars->player);
	mlx_put_image_to_window(vars->mlx, vars->win,
		minimap_buffer.img, MINIMAP_X_OFFSET, MINIMAP_Y_OFFSET);
	mlx_destroy_image(vars->mlx, minimap_buffer.img);
}

/*
Parameters:

Description:

Return value:

*/
static void	render_screen(t_vars *vars)
{
	create_image(vars->mlx, &vars->scrn_buff, WIN_WIDTH, WIN_HEIGHT);
	init_bg_mlx(vars->colours, &vars->scrn_buff);
	render_view(vars->texture_cache,
		vars->player, vars->map.map, &vars->scrn_buff);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->scrn_buff.img, 0, 0);
	render_minimap(vars);
	mlx_destroy_image(vars->mlx, vars->scrn_buff.img);
}

static int	loop_game(t_vars *vars)
{
	if (vars->mouse.m_pause == 0)
		handle_mouse(vars, &vars->mouse);
	render_screen(vars);
	return (EXIT_SUCCESS);
}

/*
Parameters:
config - Address of config structure returned after parsing and validation

Description:
Handles all mlx relation functions.

Return value:
Returns nothing.
*/
void	handle_mlx(t_config *config)
{
	t_vars	vars;

	vars = (t_vars){.mouse = (t_mouse){.old_pos_x = WIN_WIDTH / 2}};
	vars.mlx = mlx_init();
	vars.map = config->map;
	if (!vars.mlx)
		error_handler("Display var not configured", "main", EIO);
	init_colours_mlx(&vars.colours, config->assets.colours, COLOURS_SIZE);
	init_config_textures_mlx(vars.mlx, &vars.texture_cache,
		config->assets.textures, TEXTURES_SIZE);
	init_player_mlx(&vars.player, vars.map.map);
	cache_minimap_assets(vars.mlx, &vars.texture_cache);
	cache_minimap(vars.map, vars.mlx, &vars.texture_cache);
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	mlx_hook(vars.win, 17, 0, exit_program_mlx, &vars);
	mlx_hook(vars.win, 2, 0, handle_keys, &vars);
	mlx_do_key_autorepeaton(vars.mlx);
	mlx_mouse_hide();
	mlx_mouse_move(vars.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_mouse_get_pos(vars.win, &vars.mouse.old_pos_x, &vars.mouse.y);
	mlx_loop_hook(vars.mlx, loop_game, &vars);
	mlx_loop(vars.mlx);
}

// replace in linux version
// mlx_mouse_move(vars.mlx, vars.win, WIN_WIDTH/2, WIN_HEIGHT/2);
// mlx_mouse_get_pos(vars.mlx, vars.win, &vars.mouse.old_pos_x, &vars.mouse.y);
// mlx_mouse_get_pos(vars.mlx, vars.win, &vars.mouse.old_pos_x, &vars.mouse.y);
