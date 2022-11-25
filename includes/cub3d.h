#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "mlx.h"
# include "libft.h"

# define WIN_WIDTH 1366
# define WIN_HEIGHT 768

# define GRID_SIZE 64

# define MINIMAP_SCALE 4
# define MINIMAP_SIZE WIN_HEIGHT/MINIMAP_SCALE
# define MINIMAP_GRID_SIZE MINIMAP_SIZE/8
# define MINIMAP_X_OFFSET WIN_WIDTH-(WIN_HEIGHT/MINIMAP_SCALE)
# define MINIMAP_Y_OFFSET 0
# define MINIMAP_OBS_SIZE MINIMAP_GRID_SIZE
# define MINIMAP_PLYR_SIZE MINIMAP_SIZE/16

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define TRANSPARENT 0xFF000000

# define MOVE_SPEED 4
# define FOV 66.0

enum e_textures{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
	TEXTURES_SIZE
};

enum e_colours{
	FLOOR = 0,
	CEILING,
	COLOURS_SIZE
};

typedef struct s_assets
{
	char	*textures[TEXTURES_SIZE];
	char	*colours[COLOURS_SIZE];
}	t_assets;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_data;

typedef struct s_cache
{
	union
	{
		struct
		{
			t_data	north;
			t_data	south;
			t_data	east;
			t_data	west;
		};
		t_data	textures[TEXTURES_SIZE];
	};
	t_data	bg;
	t_data	minimap;
	t_data	minimap_obs;
	t_data	minimap_player;
}	t_cache;

typedef struct s_colours
{
	union
	{
		struct
		{
			int		floor;
			int		ceiling;
		};
		int	colours[COLOURS_SIZE];
	}	bg;
}	t_colours;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_config
{
	t_assets	assets;
	t_map		map;
}	t_config;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	double		px;
	double		py;
	t_vector	dir_vector;
	t_vector	cam_vector;
	double		dist_to_x;
	double		dist_to_y;
	double		pdx;
	double		pdy;
}	t_player;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_cache		texture_cache;
	t_colours	colours;
	t_player	player;
	t_map		map;
}	t_vars;

// error_handler.c
void	error_handler(const char *msg, const char *func, int err_no);

// file_validator.c
void	validate_ext(const char *filename, const char *ext_to_check);

// config_parser.c
void	parse_config(const char *filename, t_config *config);

// assets_validator.c
void	validate_assets_config(const t_assets assets);

// config_parser_helper.c
int		check_assets_set(const t_assets assets);

// config_parsing_utils.c
int		is_str_empty(const char *str);
int		is_str_map(const char *str);
int		is_rgb_value(const char *str);

// map_validator_utils.c
void	fill_space(char **temp_arr, int arrlen, int size);
void	copy_into_temp(char **dst, char **src, int len);
int		get_longest_line(char **config_cache);

// map_validator.c
void	validate_map(char **map_cache);

// mlx_handler.c
void	handle_mlx(t_config *config);

// mlx_hook_functions.c
int		exit_program_mlx(t_vars *mlx);

// mlx_initializer.c
void	init_config_textures_mlx(void *p_mlx, t_cache *texture_cache,
		char *textures[], size_t size);
void	init_colours_mlx(t_colours *colours_cache,
			char *colours[], size_t size);
void	init_player_mlx(t_player *player, char **map);
void	init_bg_mlx(t_vars *vars, void *mlx, t_data *bg);

// image_utils.c
void	cache_image_from_xpm(void *mlx, t_data *img, char *path);
void	create_image(void *mlx, t_data *img, int width, int height);
void	fill_image_with_color(int *img_addr, int num_pixels, int colour);
void	copy_img(t_data *dst, t_data *src, int x, int y);

// minimap_initializer.c
void	cache_minimap_assets(void *vars, t_cache *cache);
void	cache_minimap(t_map map, void *mlx, t_cache *cache);

// player_utils.c
void	init_player_var(t_player *player, char orientation, int x, int y);
void	handle_player_movement(int key, t_player *player);

// vect_utils.c
t_vector	add_vectors(t_vector a, t_vector b);

#endif
