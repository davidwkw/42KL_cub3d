#include "cub3d.h"


static void	img_generator(void *mlx, t_data *tmp, int colour, int side)
{
	tmp->img = mlx_new_image(mlx, side, side);
	tmp->addr = mlx_get_data_addr(tmp->img, &tmp->bpp, &tmp->size_line, &tmp->endian);
	rectangle_drawer(tmp, side, side, colour);
}

static void	minimap_bg_drawer(void *mlx, t_data *mmbg)
{
	int width;
	int height;

	width = WIN_WIDTH / 6;
	height = width;
	mmbg->img = mlx_new_image(mlx, width, height); // adjust the size
	mmbg->addr = mlx_get_data_addr(mmbg->img, &mmbg->bpp, &mmbg->size_line, &mmbg->endian);
	rectangle_drawer(mmbg, width, height, 0); // adjust the colour
}

static void minimap_player_drawer(void *mlx, t_data *mmp)
{
	int	width;
	int	height;

	width = 10;
	height = width;
	mmp->img = mlx_new_image(mlx, width, height);
	mmp->addr = mlx_get_data_addr(mmp->img, &mmp->bpp, &mmp->size_line, &mmp->endian);
	rectangle_drawer(mmp, width, height, 0x54F2ED); // adjust the colour
}

static void minimap_obs_drawer(void *mlx, t_data *mmo)
{
	int	width;
	int	height;

	width = 23;
	height = width;
	mmo->img = mlx_new_image(mlx, width, height);
	mmo->addr = mlx_get_data_addr(mmo->img, &mmo->bpp, &mmo->size_line, &mmo->endian);
	rectangle_drawer(mmo, width, height, 0xFFFFF); // adjust the colour
}

/*
Parameters:
mlx - The pointer to the mlx
cache - The cache struct that contains all the assets

Description:
Will pass three items stored in the cache struct to it's
*/
void	init_minimap_assets(void *mlx, t_cache *cache)
{
	minimap_bg_drawer(mlx, &cache->minimap_bg);
	// img_generator(mlx, &cache->minimap_bg, WIN_WIDTH / 6, 0);
	// img_generator(mlx, &cache->minimap_player, 10, 0x54F2ED);
	// img_generator(mlx, &cache->minimap_obs, 23, 0xFFFFF);
}