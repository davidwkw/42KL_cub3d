#include "cub3d.h"

/*
Parameters:
map - The padded 2D array of the map
x - x coordinate of the character to be checked
y - y coordinate of the character to be checked

Description:
Recursively calls itself in 8 directions to check if each character is a
valid character.

Return value:
Returns true if valid, false otherwise.
*/
static int	check_enclosed(char **map, int x, int y)
{
	if (x < 0 || y < 0 || y > ft_2darrlen(map) - 1 || x > ft_strlen(map[y]) - 1)
		return (true);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (true);
	if (x == 0 || x == ft_strlen(map[y]) - 1
		|| y == 0 || y == ft_2darrlen(map) - 1)
		return (false);
	if (map[y][x] == ' ')
		return (false);
	map[y][x] = 'X';
	return (check_enclosed(map, x - 1, y - 1)
		&& check_enclosed(map, x + 0, y - 1)
		&& check_enclosed(map, x + 1, y - 1)
		&& check_enclosed(map, x - 1, y - 0)
		&& check_enclosed(map, x + 1, y - 0)
		&& check_enclosed(map, x - 1, y + 1)
		&& check_enclosed(map, x + 0, y + 1)
		&& check_enclosed(map, x + 1, y + 1));
}

/*
Parameters:
<<<<<<< HEAD
map - The padded 2D array of the map

Description:
Loops through `map` and executes the check_enclosed function upon finding
a '0' character

Return value:
Returns true if valid, false otherwise.
*/
static int	check_map(char **map)
{
	int	x;
	int	y;
	int	len;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0')
			{
				if (!check_enclosed(map, x, y))
					return (false);
			}
			++x;
		}
		++y;
	}
	return (true);
}

/*
Parameters:
map - The padded 2D map array
i - The row for the 2D map array
j - The index of the character in the row

Description:
Will check all 8 elements surrounding the element at index i, j
and see if there's a space character. Intended to checks if the player is
outside the enclosed map boundary

Return value:
Returns false if found an invalid character. Returns true otherwise.
*/
static int	check_plyr_oob(char **map, int i, int j)
{
	int	row_limit;

	row_limit = ft_2darrlen(map);
	if (j <= 0 || i <= 0 || i == row_limit - 1 || j == ft_strlen(map[i]) - 1)
		return (false);
	return (!(map[i - 1][j - 1] == ' '
		|| map[i - 0][j - 1] == ' '
		|| map[i + 1][j - 1] == ' '
		|| map[i - 1][j - 0] == ' '
		|| map[i + 1][j - 0] == ' '
		|| map[i - 1][j + 1] == ' '
		|| map[i + 0][j + 1] == ' '
		|| map[i + 1][j + 1] == ' '
		));
}

/*
Parameters:
map - The padded 2D array of the map configuration

Description:
The function will loop through 'map' and counts the number
of either N, S, W, E characters present in the map.

Return value:
Will return 0 if the count is not exactly 1. Returns 1 otherwise.
*/
static	int	check_duplicates(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = -1;
	while (map[++i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr("NSWE", map[i][j]) != NULL)
			{
				if (check_plyr_oob(map, i, j) == false)
					return (false);
				count++;
			}
			j++;
		}
	}
	if (count != 1)
		return (false);
	return (true);
}

/*
Parameters:
config_cache - Map section of the cached config.

Description:
Constructs a temporary rectangular map padded with spaces to validate.

Return value:
Returns nothing.
*/
void	validate_map(char **map_cache)
{
	char	**temp_arr;
	int		longest;

	longest = get_longest_line(map_cache);
	temp_arr = malloc(sizeof(char *) * (ft_2darrlen(map_cache) + 1));
	temp_arr[ft_2darrlen(map_cache)] = NULL;
	fill_space(temp_arr, ft_2darrlen(map_cache), longest);
	copy_into_temp(temp_arr, map_cache, longest);
	if (check_duplicates(temp_arr) == 0)
		error_handler("Player position is not 1", "validate_map", EIO);
	if (check_map(temp_arr) == false)
		error_handler("Invalid map structure", "validate_map", EIO);
	ft_free2d(temp_arr);
}
=======
config_cache - the temporary 2D array that stores the lines from .cub.
i - the string index
j - the character index

Description:
Will loop through the elements surrounding the element at index i and j

Return value:
Return false if it encounters an invalid character surrounding the element to be checked
*/
// source: https://stackoverflow.com/questions/652106/finding-neighbours-in-a-two-dimensional-array
// still might need to do boundary checking
int check_surrounding_elem(char **config_cache, int i, int j)
{
	int	row_limit;
	int col_limit;
	int	x;
	int y;

	row_limit = ft_2darrlen(config_cache);
	if (row_limit > 0)
	{
		col_limit = ft_strlen(config_cache[i]);
		x = ft_max(0, i - 1);
		while (x <= ft_min(i + 1, row_limit))
		{
			y = ft_max(0, j - 1);
			while (y <= ft_min(j + 1, col_limit))
			{
				if ((x != i || y != j) && check_elem(config_cache[x][y]))
					return (0);
				y++;
			}
			x++;
		}
	}
	return (1);
}

/*
Parameter:
config_cache - a temporrary 2D array that stores all the lines
from the .cub file. The parameter is passed while the pointer is already being pointed
at the line where the map starts. This is done from the function caller side.

Description:
It will scan through each character elements in the map and upon encountering a space
character, it will call the check_surrounding_elem that will check the characters
surrounding the space.

Return value:
Returns false if check_surrounding_elem encounters an error. Else, returns true.
*/
int	check_space_validity(char **config_cache)
{
	int i;
	int j;

	i = 0;
	while (i < ft_2darrlen(config_cache))
	{
		j = 0;
		while (j < ft_strlen(config_cache[i]))
		{
			if (config_cache[i][j] == ' ')
			{
				if (check_surrounding_elem(config_cache, i, j) == 0) // can combine this if check with the previous if check using &&
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	validate_map(char **config_cache)
{
	if (check_space_validity(config_cache) == 0)
		error_handler("Invalid map structure", "validate_map", EIO);
}
>>>>>>> f0d4cf028c9740a0e67318ce9f995032109421d6
