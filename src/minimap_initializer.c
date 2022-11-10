#include "cub3d.h"

static t_data	*get_minimap_asset(t_cache *cache, char c)
{
	if (c == '1')
		return (&cache->minimap_obs);
	else
		return NULL;
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
	create_image(mlx, &cache->minimap_obs,
				MINIMAP_OBS_SIZE, MINIMAP_OBS_SIZE);
	fill_image_with_color((int *)cache->minimap_obs.addr,
						cache->minimap_obs.width*cache->minimap_obs.height,
						WHITE);
	create_image(mlx, &cache->minimap_player,
				MINIMAP_PLYR_SIZE, MINIMAP_PLYR_SIZE);
	fill_image_with_color((int *)cache->minimap_player.addr,
						cache->minimap_player.width*cache->minimap_player.height,
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
	int		x;
	int		y;
	t_data *asset;

	create_image(mlx, &cache->minimap,
				map.width*MINIMAP_GRID_SIZE, map.height*MINIMAP_GRID_SIZE);
	fill_image_with_color((int *)cache->minimap.addr,
						cache->minimap.width*cache->minimap.height,
						BLUE);
	y = 0;
	while (map.map[y] != NULL)
	{
		x = 0;
		while (map.map[y][x] != '\0')
		{
			asset = get_minimap_asset(cache, map.map[y][x]);
			copy_img(&cache->minimap, asset,
					x*MINIMAP_GRID_SIZE, y*MINIMAP_GRID_SIZE);	
			++x;
		}
		++y;
	}
}
