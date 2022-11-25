#include "cub3d.h"

t_vector add_vectors(t_vector a, t_vector b)
{
	t_vector ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}
