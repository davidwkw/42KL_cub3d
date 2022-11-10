#include "cub3d.h"

/*
Parameters:
player - Address of player structure to initialize
oritentation - player orientation in map
x - x coordinate of player
y - y coordinate of player 

Description:
Sets the player's coordinates, angle and delta x and y repectively.

Return value:
Returns nothing.
*/
void	init_player_var(t_player *player, char orientation, int x, int y)
{
	player->px = x;
	player->py = y;
	if (orientation == 'E')
		player->pa = M_PI;
	else if (orientation == 'N')
		player->pa = M_PI/2;
	else if (orientation == 'W')
		player->pa = 0;
	else if (orientation == 'S')
		player->pa = 3*M_PI/2;
	player->pdx = cos(player->pa);
	player->pdy = sin(player->pa);
}

/*
Parameters:
rad_angle - Angle of triangle in radians
dx - address of dx variable to be set by the function
dy - address of du variable to be set by the function

Description:
Takes in an angle in radians of an angle in a circle and sets the dx and dy
variables passed in to it.

Return value:
Returns a float value corrected to be possible within a circle.

*Note: Fairly generic function. Should be located in a separate utils file.
*/
float	calc_radial_dx_dy(float rad_angle, float *dx, float *dy)
{
	if (rad_angle < 0)
		rad_angle += 2*M_PI;
	else if (rad_angle > 2*M_PI)
		rad_angle -= 2*M_PI;
	*dx = cos(rad_angle);
	*dy = sin(rad_angle);
	return (rad_angle);
}

/*
Parameters:
key - Keycode of button pressed
player - player structure containing player coordinates and player's dx and dy

Description:
Handles WASD movement keys on mac and linux for player movement

Return value:
Returns nothing.
*/
void	handle_player_movement(int key, t_player *player)
{
	if (key == 'w' || key == 13)
	{
		player->py += (player->pdy * MOVE_SPEED);
		player->px += (player->pdx * MOVE_SPEED);
	}
	else if (key == 's' || key == 1)
	{
		player->py -= (player->pdy * MOVE_SPEED);
		player->px -= (player->pdx * MOVE_SPEED);
	}
	else if (key == 'a' || key == 0)
		player->pa = calc_radial_dx_dy(player->pa - 0.1,
									&player->pdx, &player->pdy);
	else if (key == 'd' || key == 2)
		player->pa = calc_radial_dx_dy(player->pa + 0.1,
									&player->pdx, &player->pdy);
}
