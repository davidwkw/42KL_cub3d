#include "cub3d.h"

// to refactor so that it takes into account player vector x/y rather than char.
static void set_camera_plane(char dir, t_vector *cam_vect, double fov)
{
	fov /= 2;
	if (dir == 'E')
	{	
		cam_vect->x = 0;
		cam_vect->y = tan(fov/180.0*M_PI);
	}
	else if (dir == 'N')
	{
		cam_vect->x = tan(fov/180.0*M_PI);
		cam_vect->y = 0;
	}
	else if (dir == 'W')
	{
		cam_vect->x = 0;
		cam_vect->y = -tan(fov/180.0*M_PI);
	}
	else if (dir == 'S')
	{
		cam_vect->x = -tan(fov/180.0*M_PI);
		cam_vect->y = 0;
	}
}

static void set_player_dir_vect(char dir, t_vector *p_vector)
{
	if (dir == 'E')
	{	
		p_vector->x = 1;
		p_vector->y = 0;
	}
	else if (dir == 'N')
	{
		p_vector->x = 0;
		p_vector->y = -1;
	}
	else if (dir == 'W')
	{
		p_vector->x = -1;
		p_vector->y = 0;
	}
	else if (dir == 'S')
	{
		p_vector->x = 0;
		p_vector->y = 1;
	}
}

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
	set_player_dir_vect(orientation, &player->dir_vect);
	set_camera_plane(orientation, &player->cam_vect, FOV);
}

static void handle_forw_back(char key, t_player *p, t_map map)
{
	if (key == 'w' || key == 13)
	{
		if (map.map[(int)(p->py + p->dir_vect.y * MOVE_SPEED)][(int)p->px] != '1')
			p->py += p->dir_vect.y * MOVE_SPEED;
		if (map.map[(int)p->py][(int)(p->px  + p->dir_vect.x * MOVE_SPEED)] != '1')
			p->px += p->dir_vect.x * MOVE_SPEED;
	}
	else if (key == 's' || key == 1)
	{
		if (map.map[(int)(p->py - p->dir_vect.y * MOVE_SPEED)][(int)p->px] != '1')
			p->py -= p->dir_vect.y * MOVE_SPEED;
		if (map.map[(int)p->py][(int)(p->px  - p->dir_vect.x * MOVE_SPEED)] != '1')
			p->px -= p->dir_vect.x * MOVE_SPEED;
	}
}

static void	handle_rotation(char key, t_player *p)
{
	double	prev_dir_x;
	double	prev_plane_x;

	if (key == 'a' || key == 0)
	{
		prev_dir_x = p->dir_vect.x;
		p->dir_vect.x = p->dir_vect.x * cos(-ROT_SPEED)
						- p->dir_vect.y * sin(-ROT_SPEED);
		p->dir_vect.y = prev_dir_x * sin(-ROT_SPEED)
						+ p->dir_vect.y * cos(-ROT_SPEED);
		prev_plane_x = p->cam_vect.x;
		p->cam_vect.x = p->cam_vect.x * cos(-ROT_SPEED)
						- p->cam_vect.y * sin(-ROT_SPEED);
		p->cam_vect.y = prev_plane_x * sin(-ROT_SPEED)
						+ p->cam_vect.y * cos(-ROT_SPEED);
	}
	else if (key == 'd' || key == 2)
	{
		prev_dir_x = p->dir_vect.x;
		p->dir_vect.x = p->dir_vect.x * cos(ROT_SPEED)
						- p->dir_vect.y * sin(ROT_SPEED);
		p->dir_vect.y = prev_dir_x * sin(ROT_SPEED)
						+ p->dir_vect.y * cos(ROT_SPEED);
		prev_plane_x = p->cam_vect.x;
		p->cam_vect.x = p->cam_vect.x * cos(ROT_SPEED)
						- p->cam_vect.y * sin(ROT_SPEED);
		p->cam_vect.y = prev_plane_x * sin(ROT_SPEED)
						+ p->cam_vect.y * cos(ROT_SPEED);
	}
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
void	handle_player_movement(int key, t_player *p, t_map map)
{
	if (ft_strchr("ws", key) != 0 || key == 13 || key == 1)
		handle_forw_back(key, p, map);
	else if (ft_strchr("ad", key) != 0 || key == 0 || key == 2)
		handle_rotation(key, p);
}
