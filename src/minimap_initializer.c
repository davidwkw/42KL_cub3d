/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_initializer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:16:20 by kwang             #+#    #+#             */
/*   Updated: 2022/12/14 14:25:12 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_data	*get_minimap_asset(t_cache *cache, char c)
{
	if (c == '1')
		return (&cache->minimap_obs);
	else
		return (NULL);
}

/*
Parameters:
mlx - The pointer to the mlx
cache - The cache struct that contains all the assets

Description:
Caches the minimap assets.

Return value:
Returns nothing
*/
void	cache_minimap_assets(void *mlx, t_cache *cache)
{
	const double	minimap_size = WIN_HEIGHT / MINIMAP_SCALE;
	const double	minimap_obs_size = minimap_size / MINIMAP_GRID_SCALE;
	const double	minimap_plyr_size = minimap_size / MINIMAP_PLYR_SCALE;

	create_image(mlx, &cache->minimap_obs,
		minimap_obs_size, minimap_obs_size);
	fill_image_with_color((int *)cache->minimap_obs.addr,
		cache->minimap_obs.width * cache->minimap_obs.height,
		WHITE);
	create_image(mlx, &cache->minimap_player,
		minimap_plyr_size, minimap_plyr_size);
	fill_image_with_color((int *)cache->minimap_player.addr,
		cache->minimap_player.width * cache->minimap_player.height,
		GREEN);
}

/*
Parameters:
map - Copy of the t_map data structure containing a char ** for map and its
	dimensions
mlx - pointer returned by mlx_init
t_cache - data structure containing the cache of game assets

Description:
Caches the minimap.

Return value:
Returns nothing
*/
void	cache_minimap(t_map map, void *mlx, t_cache *cache)
{
	const double	minimap_size = WIN_HEIGHT / MINIMAP_SCALE;
	const double	minimap_grid_size = minimap_size / MINIMAP_GRID_SCALE;
	int				x;
	int				y;
	t_data			*asset;

	create_image(mlx, &cache->minimap,
		map.width * minimap_grid_size, map.height * minimap_grid_size);
	fill_image_with_color((int *)cache->minimap.addr,
		cache->minimap.width * cache->minimap.height,
		T70_BLUE);
	y = 0;
	while (map.map[y] != NULL)
	{
		x = 0;
		while (map.map[y][x] != '\0')
		{
			asset = get_minimap_asset(cache, map.map[y][x]);
			copy_img(&cache->minimap, asset,
				x * minimap_grid_size, y * minimap_grid_size);
			++x;
		}
		++y;
	}
}
