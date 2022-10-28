/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:11:41 by kwang             #+#    #+#             */
/*   Updated: 2022/10/28 23:03:09 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
mlx - address of mlx pointer returned from mlx_init()
img - address of the memory where the image is to be cached
path - relative path to the reference image

Description:
Uses mlx_xpm_file_to_image to cache an image in xpm format into memory.

Return value:
Returns nothing
*/
void	cache_image(void *mlx, t_data *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->size_line, &img->endian);
}

/*
Parameters:
mlx - address of mlx pointer returned from mlx_init()
canvas - address of the image data structure to be populated with new image
width - dimension of image
height - dimension of image

Description:
Uses mlx_new_image to create blank image that is saved into the address 
of the image data structure passed into it.

Return value:
Returns nothing
*/
void	create_image(void *mlx, t_data *canvas, int width, int height)
{
	canvas->img = mlx_new_image(mlx, width, height);
    canvas->addr = mlx_get_data_addr(canvas->img, &canvas->bpp, &canvas->size_line, &canvas->endian);
}

/*
Parameters:
bg - data t_data struct of the background image
colour - the colour taken from the config

Description:
Loops through half of the background image's pixels and sets each pixel's colour
to the colour passed in as parameter

Return value:
Returns nothing
*/
static void	ceiling_drawer(t_data *bg, int colour)
{
	int	i;
	int	j;
	int	horizon;

	i = 0;
	horizon = WIN_HEIGHT / 2;
	while (i < horizon)
	{
		j = 0;
		while (j < WIN_WIDTH * 4)
		{
			bg->addr[j + 0] = (colour) & 0xFF;
			bg->addr[j + 1] = (colour >> 8) & 0xFF;
			bg->addr[j + 2] = (colour >> 16) & 0xFF;
			bg->addr[j + 3] = (colour >> 24);
			j+= 4;
		}
		bg->addr += bg->size_line;
		i++;
	}
}

/*
Parameters:
bg - data t_data sruct of the background image
colour - the colour taken from the config

Description:
Loops through half of the background image's pixels and sets each pixel's colour
to the colour passed in as parameter

Return value:
Returns nothing
*/
static void	floor_drawer(t_data *bg, int colour)
{
	int	i;
	int	j;

	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH * 4)
		{
			bg->addr[j + 0] = (colour) & 0xFF;
			bg->addr[j + 1] = (colour >> 8) & 0xFF;
			bg->addr[j + 2] = (colour >> 16) & 0xFF;
			bg->addr[j + 3] = (colour >> 24);
			j+= 4;
		}
		bg->addr += bg->size_line;
		i++;
	}
}

/*
Paremeters:
vars - the t_vars struct
data - the t_data type of an mlx image
w - the width of the mlx image
h - height of the mlx image
colour - the colour to set the image to

Description:
Will draw a solid rectangle

Return value:
Returns nothing
*/
void    *drawrectangle(t_vars *vars, t_data *d, int width, int height, int colour) // need to refactor this function
{
    d->img = mlx_new_image(vars->mlx, width, height);
    d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->size_line, &d->endian);
    int i, j;
    int *temp;
    temp = (int *)d->addr;
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            temp[j] = colour;
            ++j;
        }
        temp += (d->size_line / (d->bpp / 8));
        i++;
    }
}

void	init_bg_mlx(t_vars *vars, void *mlx, t_data *bg)
{
	bg->img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	bg->addr = mlx_get_data_addr(bg->img, &bg->bpp, &bg->size_line, &bg->endian);
	ceiling_drawer(bg, vars->colours.bg.ceiling);
	floor_drawer(bg, vars->colours.bg.floor);
}
