#include "cub3d.h"

/*
Parameters:
vars - the t_vars struct
tmp - the t_data struct that represents the image
colour -  this will be the new colour of the image
side - the length of the side (assuming the image is a square and not a rectangle)

Description:
The function will initialize the void img pointer in the t_data
struct  using the mlx_new_image() function
and draws the shape and colourize it

Return value:
Nothing is returned
*/
static void	img_generator(t_vars *vars, t_data *tmp, int colour, int side)
{
	tmp->img = mlx_new_image(vars->mlx, side, side);
	tmp->addr = mlx_get_data_addr(tmp->img, &tmp->bpp, &tmp->size_line, &tmp->endian);
	rectangle_drawer(vars, tmp, side, side, colour);
}

/*
Parameters:
vars - the t_vars struct
mmbg - stands for MiniMap BackGround. It is the t_data struct that represents the image

Description:
The function will initialize the void img pointer in the t_data
struct  using the mlx_new_image() function and draws the shape and colourize it.
However, the minimap is not necessarily a square so the the width, height and colour needs
to be deterimined inside the function

Return value:
Nothing is returned
*/
static void	minimap_bg_drawer(t_vars *vars, t_data *mmbg)
{
	int width;
	int height;

	width = WIN_WIDTH / 6;
	height = width;
	mmbg->img = mlx_new_image(vars->mlx, width, height); // adjust the size
	mmbg->addr = mlx_get_data_addr(mmbg->img, &mmbg->bpp, &mmbg->size_line, &mmbg->endian);
	rectangle_drawer(vars, mmbg, width, height, 0); // adjust the colour
}

/*
Parameters:
vars - the t_vars struct
mmp - stands for MiniMap Player. It is the t_data struct that represents the image

Description:
The function will initialize the void img pointer in the t_data
struct  using the mlx_new_image() function and draws the shape and colourize it.
However, the minimap player is not necessarily a square so the the width, height and colour needs
to be deterimined inside the function

Return value:
Nothing is returned
*/
static void minimap_player_drawer(t_vars *vars, t_data *mmp)
{
	int	width;
	int	height;

	width = 10;
	height = width;
	mmp->img = mlx_new_image(vars->mlx, width, height);
	mmp->addr = mlx_get_data_addr(mmp->img, &mmp->bpp, &mmp->size_line, &mmp->endian);
	rectangle_drawer(vars, mmp, width, height, 0x54F2ED); // adjust the colour
}

/*
Parameters:
vars - the t_vars struct
mmp - stands for MiniMap Obstacle. It is the t_data struct that represents the image

Description:
The function will initialize the void img pointer in the t_data
struct  using the mlx_new_image() function and draws the shape and colourize it.
However, the minimap obstacle is not necessarily a square so the the width, height and colour needs
to be deterimined inside the function

Return value:
Nothing is returned
*/
static void minimap_obs_drawer(t_vars *vars, t_data *mmo)
{
	int	width;
	int	height;

	width = 23;
	height = width;
	mmo->img = mlx_new_image(vars->mlx, width, height);
	mmo->addr = mlx_get_data_addr(mmo->img, &mmo->bpp, &mmo->size_line, &mmo->endian);
	rectangle_drawer(vars, mmo, width, height, 0xFFFFF); // adjust the colour
}

/*
Parameters:
mlx - The pointer to the mlx
cache - The cache struct that contains all the assets

Description:
Will pass three items stored in the cache struct to it's designated functions
to be initialized and drawn

Return value:
Returns nothing
*/
void	init_minimap_assets(t_vars *vars, t_cache *cache)
{
	minimap_bg_drawer(vars->mlx, &cache->minimap_bg);
	// img_generator(vars, &cache->minimap_bg, WIN_WIDTH / 6, 0);
	// img_generator(vars, &cache->minimap_player, 10, 0x54F2ED);
	// img_generator(vars, &cache->minimap_obs, 23, 0xFFFFF);
}