#include "cub3d.h"

void handle_forw_back(t_player *p, t_map map, int dir)
{
	if (dir == FORWARD)
	{
		if (map.map[(int)(p->py + p->dir_vect.y * MOVE_SPEED)][(int)p->px] != '1')
			p->py += p->dir_vect.y * MOVE_SPEED;
		if (map.map[(int)p->py][(int)(p->px  + p->dir_vect.x * MOVE_SPEED)] != '1')
			p->px += p->dir_vect.x * MOVE_SPEED;
	}
	else if (dir == BACKWARD)
	{
		if (map.map[(int)(p->py - p->dir_vect.y * MOVE_SPEED)][(int)p->px] != '1')
			p->py -= p->dir_vect.y * MOVE_SPEED;
		if (map.map[(int)p->py][(int)(p->px  - p->dir_vect.x * MOVE_SPEED)] != '1')
			p->px -= p->dir_vect.x * MOVE_SPEED;
	}
}

void	handle_left_right(t_player *p, t_map map, int dir)
{
	if (dir == RIGHT)
		handle_rotation(p, M_PI/2);
	else if (dir == LEFT)
		handle_rotation(p, -(M_PI/2));
	handle_forw_back(p, map, FORWARD);
	if (dir == RIGHT)
		handle_rotation(p, -(M_PI/2));
	else if (dir == LEFT)
		handle_rotation(p, M_PI/2);
}

void	handle_rotation(t_player *p, double rot_speed)
{
	double	prev_dir_x;
	double	prev_plane_x;

	prev_dir_x = p->dir_vect.x;
	p->dir_vect.x = p->dir_vect.x * cos(rot_speed)
					- p->dir_vect.y * sin(rot_speed);
	p->dir_vect.y = prev_dir_x * sin(rot_speed)
					+ p->dir_vect.y * cos(rot_speed);
	prev_plane_x = p->cam_vect.x;
	p->cam_vect.x = p->cam_vect.x * cos(rot_speed)
					- p->cam_vect.y * sin(rot_speed);
	p->cam_vect.y = prev_plane_x * sin(rot_speed)
					+ p->cam_vect.y * cos(rot_speed);
}
