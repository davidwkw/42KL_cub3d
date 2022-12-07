/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/12/06 18:33:50 by kwang            ###   ########.fr       */
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
int	handle_keys(int key, t_vars *vars)
{
	printf("%d\n", key);
	if (ft_strchr("wasd", key) != NULL || (key >= 0 && key <= 2) || key == 13)
		handle_player_movement(key, &vars->player, vars->map);
	if (key == 65307 || key == 53)
	{
		printf("Quitting programme\n");
		exit_program_mlx(vars);
	}
	return (EXIT_SUCCESS);
}

/*
Parameters:

Description:

Return value:

*/
int	render_screen(t_vars *vars)
{
	create_image(vars->mlx, &vars->scrn_buff, WIN_WIDTH, WIN_HEIGHT);
	init_bg_mlx(vars, vars->mlx, &vars->scrn_buff);
	perform_raycast(vars->texture_cache, vars->player, vars->map.map, &vars->scrn_buff);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->scrn_buff.img, 0, 0);
	render_minimap(vars);
	mlx_destroy_image(vars->mlx, vars->scrn_buff.img);
	return(EXIT_SUCCESS);
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

	vars = (t_vars){};
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
	mlx_loop_hook(vars.mlx, render_screen, &vars);
	mlx_loop(vars.mlx);
}
