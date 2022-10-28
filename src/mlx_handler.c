/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/10/28 13:30:53 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:

Description:

Return value:

*/
int	key_handler(int key, t_vars *mlx)
{
	if (key == 65307 || key == 53)
	{
		printf("Quitting programme\n");
		exit_program_mlx(mlx);
	}
	return (EXIT_SUCCESS);
}

/*
Parameters:

Description:

Return value:

*/
int	screen_renderer(t_vars *vars)
{
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
	init_bg_mlx(&vars, vars.mlx, &vars.texture_cache.bg);
	init_player_mlx(&vars.player, vars.map);
	init_minimap_assets(&vars, &vars.texture_cache);
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	mlx_hook(vars.win, 17, 0, exit_program_mlx, &vars);
	mlx_key_hook(vars.win, key_handler, &vars);
	mlx_loop_hook(vars.mlx, screen_renderer, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.texture_cache.bg.img, 0, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.texture_cache.minimap_bg.img, 1139, 0);
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.texture_cache.minimap_obs.img, 1150, 100);
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.texture_cache.minimap_player.img, 1252, 113);
	mlx_loop(vars.mlx);
}
