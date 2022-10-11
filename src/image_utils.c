/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:11:41 by kwang             #+#    #+#             */
/*   Updated: 2022/10/09 21:53:44 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cache_image(void *mlx, t_data *img, char *path)
{
	img->addr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	img->img = mlx_get_data_addr(img->addr, &img->bpp,
			&img->size_line, &img->endian);
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
data - the t_data type of an mlx image
w - the width of the mlx image
h - height of the mlx image
colour - the colour to set the image to

Description:
Will draw a solid rectangle

Return value:
Returns nothing
*/
void	rectangle_drawer(t_data *data, int w, int h, int colour)
{
	int i;
	int j;
	
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < (w * 4))
		{
			data->addr[j + 0] = (colour) & 0xFF;
			data->addr[j + 1] = (colour >> 8) & 0xFF;
			data->addr[j + 2] = (colour >> 16) & 0xFF;
			data->addr[j + 3] = (colour >> 24);
			j += 4;
		}
		data->addr += data->size_line;
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