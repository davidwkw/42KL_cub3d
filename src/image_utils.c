/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:11:41 by kwang             #+#    #+#             */
/*   Updated: 2022/11/01 17:22:34 by kwang            ###   ########.fr       */
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
void	cache_image_from_xpm(void *mlx, t_data *img, char *path)
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
void	create_image(void *mlx, t_data *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	img->width = width;
	img->height = height;
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
}

/*
Parameters:
img_address - address of the image in the form of an int * in which to start
			  filling with color
num_pixels - the number of pixels to fill with color. if a char * is passed in,
the total length of the string NEEDS to be a multiple of 4.
Description:
Function will assign the colour value to the given address until the number of 
pixels is reached.

Return value:
Returns nothing
*/
void	fill_image_with_color(int *img_addr, int num_pixels, int colour)
{
	int	i;

	i = 0;
	while (i < num_pixels)
	{
		img_addr[i] = colour;
		++i;
	}
}

/*
Parameters:
dst - destination image data structure to copy to.
src - source image data structure to copy from.
x - x coordinate on the destination address to begin copying to.
y - y coordinate on the destination address to begin copying to.
Description:
Function will assign the colour value to the given address until the number of 
pixels is reached.

Return value:
Returns nothing

*Note: Could use ft_memcpy on line 112.
*/
void	copy_img(t_data *dst, t_data *src, int x, int y)
{
	int		i;
	int		j;
	char	*temp_dst;
	char	*temp_src;

	if (dst == NULL || src == NULL)
		return ;
	temp_dst = dst->addr;
	temp_src = src->addr;
	i = -1;
	while (++i < src->height && y + i < dst->height)
	{
		j = -1;
		while (++j < src->width && x + j < dst->width)
			temp_dst[x+j] = temp_src[j];
		temp_dst += dst->size_line;
		temp_src += src->size_line;
	}
}
