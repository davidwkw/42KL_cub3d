/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:15:00 by kwang             #+#    #+#             */
/*   Updated: 2022/12/12 16:16:13 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
mlx - Address of variable containing the mlx and window pointers

Description:
Uses the mlx and windows pointer to destroy the window generated by the mlx
library

Return value:
Does not technically return a value because of exit() system call.
*/
int	exit_program_mlx(t_vars *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
        // system("leaks cub3d");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
