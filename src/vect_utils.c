/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:15:53 by kwang             #+#    #+#             */
/*   Updated: 2022/12/12 16:18:47 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	add_vectors(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

t_vector	multiply_vector(t_vector vect, double multiple)
{
	t_vector	ret;

	ret.x = vect.x * multiple;
	ret.y = vect.y * multiple;
	return (ret);
}
