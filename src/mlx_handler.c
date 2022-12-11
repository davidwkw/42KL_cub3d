/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/12/11 19:39:16 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_minimap(t_data *minimap_buff, t_cache cache, t_player p)
{
	copy_img(minimap_buff, &cache.minimap,
			(MINIMAP_SIZE/2 -p.px*MINIMAP_GRID_SIZE),
			(MINIMAP_SIZE/2 - p.py*MINIMAP_GRID_SIZE));
	copy_img(minimap_buff, &cache.minimap_player,
			minimap_buff->width/2 - MINIMAP_PLYR_SIZE/2,
			minimap_buff->height/2 - MINIMAP_PLYR_SIZE/2);
}

void	render_minimap(t_vars *vars)
{
	t_data	minimap_buffer;

	create_image(vars->mlx, &minimap_buffer, MINIMAP_SIZE, MINIMAP_SIZE);
	fill_image_with_color((int *)minimap_buffer.addr, minimap_buffer.width*minimap_buffer.height, TRANSPARENT);
	paint_minimap(&minimap_buffer, vars->texture_cache, vars->player);
	// copy_img(&vars->scrn_buff, &minimap_buffer, MINIMAP_X_OFFSET, MINIMAP_Y_OFFSET);
	mlx_put_image_to_window(vars->mlx, vars->win, minimap_buffer.img, MINIMAP_X_OFFSET, MINIMAP_Y_OFFSET);
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
	render_view(vars->texture_cache, vars->player, vars->map.map, &vars->scrn_buff);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->scrn_buff.img, 0, 0);
	render_minimap(vars);
	mlx_destroy_image(vars->mlx, vars->scrn_buff.img);
}

static int loop_game(t_vars *vars)
{
	handle_mouse(vars, &vars->m_pos);
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

	vars = (t_vars){.m_pos = (t_mouse){.old_pos_x = WIN_WIDTH/2}};
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
	mlx_key_hook(vars.win, handle_keys, &vars);
	mlx_mouse_hide(vars.mlx, vars.win);
	mlx_mouse_move(vars.mlx, vars.win, WIN_WIDTH/2, WIN_HEIGHT/2);
	mlx_mouse_get_pos(vars.mlx, vars.win, &vars.m_pos.old_pos_x, &vars.m_pos.y);
	mlx_loop_hook(vars.mlx, loop_game, &vars);
	mlx_loop(vars.mlx);
}
