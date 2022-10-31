#include "cub3d.h"

void	init_player_var(t_player *player, char **map, int x, int y)
{
	player->coords.x = x;
	player->coords.y = y;
	if (map[y][x] == 'E')
		player->pa = 0;
	else if (map[y][x] == 'N')
		player->pa = M_PI/2;
	else if (map[y][x] == 'W')
		player->pa = M_PI;
	else if (map[y][x] == 'S')
		player->pa = 3*M_PI/2;
	player->pdx = cos(player->pa)*MOVE_SPEED;
	player->pdy = sin(player->pa)*MOVE_SPEED;
}
