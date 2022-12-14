# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 17:03:19 by kwang             #+#    #+#              #
#    Updated: 2022/12/14 16:55:46 by kwang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES =		main.c \
				error_handler.c \
				file_validator.c \
				assets_validator.c \
				config_parsing_utils.c \
				config_parser.c \
				mlx_handler.c \
				mlx_hook_functions.c \
				mlx_initializer.c \
				config_parser_helper.c \
				image_utils.c \
				map_validator.c \
				map_validator_utils.c \
				minimap_initializer.c \
				player_utils.c \
				vect_utils.c \
				view_renderer.c \
				utils.c \
				input_handler.c \
				raycasting_utils.c \
				movement_utils.c

OBJ_DIR = obj/

SRC_DIR = src/

OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES) -I/usr/include/ -I$(LIBFTDIR) -O3

LINUXMLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

MACMLXFLAGS = -Lmlx_mac -lmlx -framework OpenGL -framework AppKit

UNAME_S := $(shell uname -s)

    ifeq ($(UNAME_S),Linux)
        CFLAGS += -Imlx_linux
		MLXFLAGS += $(LINUXMLXFLAGS)
		MLXDIR = mlx_linux
		MLX = $(MLXDIR)/libmlx_Linux.a
    else ifeq ($(UNAME_S),Darwin)
        CFLAGS += -Imlx -Imlx_mac
		MLXFLAGS += $(MACMLXFLAGS)
		MLXDIR = mlx_mac
		MLX = $(MLXDIR)/libmlx.a
    endif

INCLUDES = includes

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a

LIBFTFLAGS = -L$(LIBFTDIR) -lft -I$(LIBFTDIR)

NAME = cub3D

all : $(NAME)

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT) :
				@make -C $(LIBFTDIR) all

$(MLX) :
				@make -C $(MLXDIR)

$(NAME):		$(OBJS) $(INCLUDES)/cub3d.h $(LIBFT) $(MLX)
				@echo "Creating $(NAME).."
				@echo "Your display variable is $$DISPLAY"
				@git submodule init
				@git submodule update
				$(CC) $(OBJS) -o $@ $(LIBFTFLAGS) $(MLXFLAGS)

bonus : 		${NAME}

clean :
				@echo "Cleaning all .o files.."
				@make -C $(LIBFTDIR) clean
				@rm -rf $(OBJ_DIR)
				
fclean : 		clean
				@echo "Cleaning $(NAME)"
				@make -C $(LIBFTDIR) fclean
				@make -C $(MLXDIR) clean
				@rm -f $(NAME)

re : 			fclean all

run	: 			all
				./cub3D maps/basic_map.cub

.PHONY : all bonus clean fclean re run
