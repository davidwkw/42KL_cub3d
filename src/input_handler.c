#include "cub3d.h"

static void	handle_mouse_pause(t_mouse *mouse)
{
	mouse->m_pause = mouse->m_pause ^ (1 << 1);
	if (mouse->m_pause == 1)
		mlx_mouse_show();
	else if (mouse->m_pause == 0)
		mlx_mouse_hide();
}

/*
Parameters:

Description:

Return value:

*/
int	handle_keys(int key, t_vars *vars)
{
	if (ft_strchr("wasd", key) != NULL || (key >= 0 && key <= 2) || key == 13)
		handle_player_movement(key, &vars->player, vars->map);
	if (key == 'p' || key == 35)
		handle_mouse_pause(&vars->mouse);
	if (key == 65307 || key == 53)
	{
		printf("Quitting programme\n");
		exit_program_mlx(vars);
	}
	return (EXIT_SUCCESS);
}

void	handle_mouse(t_vars *vars, t_mouse *mouse)
{
	int						m_diff;
	int						dir;
	struct timeval			tv;
	static struct timeval	prev;

	gettimeofday(&tv, NULL);
	if (tv.tv_sec == prev.tv_sec && (tv.tv_usec - prev.tv_usec) < (1000000 / M_POLL_RATE))
		return ;
	mlx_mouse_get_pos(vars->win, &vars->mouse.x, &vars->mouse.y);
	dir = vars->mouse.x - mouse->old_pos_x;
	m_diff = ft_absolute(dir);
	if (dir > M_MOVE_THRESHOLD)
		handle_rotation(&vars->player, m_diff * M_SENSITIVITY);
	else if (dir < -M_MOVE_THRESHOLD)
		handle_rotation(&vars->player, -(m_diff * M_SENSITIVITY));
	mlx_mouse_move(vars->win, WIN_WIDTH/2, WIN_HEIGHT/2);
	mlx_mouse_get_pos(vars->win, &vars->mouse.old_pos_x, &vars->mouse.y);
	prev = tv;
}

// replace in linux version
// mlx_mouse_get_pos(vars->mlx, vars->win, &vars->mouse.x, &vars->mouse.y);
// mouse->old_pos_x = vars->mouse.x;
