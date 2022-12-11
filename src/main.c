/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:30:08 by kwang             #+#    #+#             */
/*   Updated: 2022/10/05 22:12:47 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_config	config;

	errno = 0;
	if (argc != 2)
	{
		printf("Usage: %s [<MAP_NAME>.cub]\n", argv[0]);
		return (EXIT_FAILURE);
	}
	parse_config(argv[1], &config);
	handle_mlx(&config);
	return (EXIT_SUCCESS);
}
