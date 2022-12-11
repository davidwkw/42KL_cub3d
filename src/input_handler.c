#include "cub3d.h"

/*
Parameters:

Description:

Return value:

*/
int	handle_keys(int key, t_vars *vars)
{
	if (ft_strchr("wasd", key) != NULL || (key >= 0 && key <= 2) || key == 13)
		handle_player_movement(key, &vars->player, vars->map);
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
	mlx_mouse_get_pos(vars->mlx, vars->win, &vars->m_pos.x, &vars->m_pos.y);
	dir = vars->m_pos.x - mouse->old_pos_x;
	m_diff = ft_absolute(dir);
	if (dir > M_MOVE_THRESHOLD)
		handle_rotation(&vars->player, m_diff * M_SENSITIVITY);
	else if (dir < -M_MOVE_THRESHOLD)
		handle_rotation(&vars->player, -(m_diff * M_SENSITIVITY));
	// mlx_mouse_move(vars->mlx, vars->win, WIN_WIDTH/2, WIN_HEIGHT/2);
	mouse->old_pos_x = vars->m_pos.x;
	prev = tv;
}
