/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:54 by kwang             #+#    #+#             */
/*   Updated: 2022/11/01 22:25:53 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:

Description:

Return value:

*/
int	handle_keys(int key, t_vars *vars)
{
	printf("%d\n", key);
	if (ft_strchr("WASD", key) != NULL || (key >= 0 && key <= 2) || key == 13)
		handle_player_movement(key, &vars->player);
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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->texture_cache.bg.img, 0, 0);
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.texture_cache.minimap.img, MINIMAP_X_OFFSET, MINIMAP_Y_OFFSET);
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
	init_player_mlx(&vars.player, vars.map.map);
	cache_minimap_assets(vars.mlx, &vars.texture_cache);
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	mlx_hook(vars.win, 17, 0, exit_program_mlx, &vars);
	mlx_key_hook(vars.win, handle_keys, &vars);
	mlx_loop_hook(vars.mlx, render_screen, &vars);
	mlx_loop(vars.mlx);
}
