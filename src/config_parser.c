/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 21:57:22 by kwang             #+#    #+#             */
/*   Updated: 2022/12/14 14:24:32 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Parameters:
textures - Address of t_texture data type of populate with a string from
			configuration file.
str - single string from config cache that should represent the texture to be
		assigned and the string representation of the configuration.

Description:
Iterates through a preset list of textures that is required to be assigned to
and assigned the matched configuration to the texture. Once function call
assigns to only one texture.

Return value:
Returns nothing. Throws errors configuration is invalid.
*/
static void	set_config(t_assets *assets, const char *str)
{
	char		**split;
	// const char	*textures[4] = {"NO", "SO", "EA", "WE"};
	// const char	*colours[2] = {"F", "C"};
	const char	*asset_code[6] = {"NO", "SO", "EA", "WE", "F", "C"};
	size_t		i;

	split = ft_split(str, ' ');
	if (ft_2darrlen(split) != 2)
		error_handler("Wrong configuration given", "set_config", EIO);
	i = -1;
	while (++i < TEXTURES_SIZE + COLOURS_SIZE)
	{
		if (i < 4 && !ft_strcmp(split[0], asset_code[i]))
		{
			if (assets->textures[i] != NULL)
				error_handler("Duplicate asset value", "set_config", EIO);
			assets->textures[i] = ft_strdup(split[1]);
		}
		if (i > 3 && !ft_strcmp(split[0], asset_code[i] - 4))
		{
			if (assets->colours[i - 4] != NULL)
				error_handler("Duplicate asset value", "set_config", EIO);
			assets->colours[i - 4] = ft_strdup(split[1]);
		}	
	}
	// while (++i < TEXTURES_SIZE)
	// {
	// 	if (!ft_strcmp(split[0], textures[i]))
	// 		assets->textures[i] = ft_strdup(split[1]);
	// }
	// i = -1;
	// while (++i < COLOURS_SIZE)
	// {
	// 	if (!ft_strcmp(split[0], colours[i]))
	// 		assets->colours[i] = ft_strdup(split[1]);
	// }
	ft_free2d(split);
}

/*
Parameters:
textures - Address of t_texture data type of populated with strings from
			configuration file.
config_cache - Value of a nested array that was populated with content from
				config file

Description:
Reads from cached configuration file and populates t_texture data structure
with strings required for image and color caching. No validation is done during
function call.

Return value:
Returns nothing. Throws errors structure fails to be completely populated.
*/
static void	set_assets_config(t_assets *assets, const char **config_cache)
{
	size_t	i;

	i = 0;
	if (config_cache == NULL || config_cache[0] == NULL)
		error_handler("Config non-existent", "set_assets_config", EIO);
	while (!is_str_map(config_cache[i]) && (i < (TEXTURES_SIZE + COLOURS_SIZE)))
	{
		set_config(assets, config_cache[i]);
		i++;
	}
	if (!check_assets_set(*assets))
		error_handler("Incomplete textures amount", "set_assets_config", EIO);
}

/*
Parameters:
fd - opened file descriptor belonging to the configuration file.
config_cache - address of a nested array that is populated with content from
				config file

Description:
Populates a nested array of strings obtained via get_next_line and stores them 
within config_cache for easy random access. Discards any line that only contains
whitespace characters.

Return value:
Returns nothing. Throws errors if reading or caching fails.
*/
static void	cache_config(int fd, char ***config_cache)
{
	char	*line;
	t_list	*head;
	t_list	*lst;
	int		map_reached;

	head = NULL;
	map_reached = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (is_start_of_map(line) == 1 && map_reached == 0)
			map_reached = 1;
		if (is_str_empty(line) == true && map_reached == 0)
		{
			free(line);
			continue ;
		}
		lst = ft_lstnew(line);
		if (!lst->content)
			error_handler("Str duplicate error", "cache_config", EIO);
		ft_lstadd_back(&head, lst);
	}
	*config_cache = (char **)ft_lst_to_arr(head);
	ft_lstclear(&head, NULL);
	free(line);
}

/*
Parameters:
map - address of map variable to be used by game logic
map_config - address map config obtained from config file

Description:
Takes a pointer to a nested array of a map and duplicates it into a map
variable to be used by game logic.

Return value:
Returns nothing.
*/
static void	cache_map(t_map *map, char **map_config)
{
	size_t	i;
	size_t	temp;
	char	*map_end;

	i = 0;
	map->width = 0;
	map->height = ft_2darrlen(map_config);
	map->map = malloc(sizeof(char *) * (map->height));
	while (map_config[i] != NULL)
	{
		map_end = ft_strrchr(map_config[i], '1');
		map->map[i] = ft_substr(map_config[i], 0, map_end - map_config[i] + 1);
		temp = ft_strlen(map->map[i]);
		if (temp > (size_t)map->width)
			map->width = temp;
		++i;
	}
	map->map[i] = NULL;
}

/*
Parameters:
filename - string that represent config file in .cub extension
vars - address of custom data structure that holds essential program data

Description:
Takes a configuration file, validates its extension, validates the configuration
file contents, and assigns the essential configuration data contained in t_vars
data structure.

Return value:
Returns nothing. Throws errors if any validation fails
*/
void	parse_config(const char *filename, t_config *config)
{
	int		fd;
	char	**config_cache;

	*config = (t_config){};
	validate_ext(filename, "cub");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_handler("Failure to open file", "parse_map", 0);
	cache_config(fd, &config_cache);
	set_assets_config(&config->assets, (const char **)config_cache);
	validate_assets_config(config->assets);
	validate_map(config_cache + (TEXTURES_SIZE + COLOURS_SIZE));
	cache_map(&config->map, config_cache + (TEXTURES_SIZE + COLOURS_SIZE));
	ft_free2d(config_cache);
	close(fd);
}
