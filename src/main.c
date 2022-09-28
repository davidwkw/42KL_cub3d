/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:25 by kwang             #+#    #+#             */
/*   Updated: 2022/09/28 16:13:27 by wwan-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_config config;

	if (argc != 2)
	{
		printf("Usage: %s [<MAP_NAME>.cub]\n", argv[0]);
		return (EXIT_FAILURE);
	}
	parse_config(argv[1], &config);

	return (EXIT_SUCCESS);
}


// just adding a new line here to test git
// added a second line