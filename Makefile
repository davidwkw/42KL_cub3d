# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 17:03:19 by kwang             #+#    #+#              #
#    Updated: 2022/12/11 18:56:08 by kwang            ###   ########.fr        #
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

# CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES) -I/usr/include/ -Imlx_linux -O3
CFLAGS = -I$(INCLUDES) -I/usr/include/ -I$(LIBFTDIR)

LINUXMLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

MACMLXFLAGS = -lmlx -framework OpenGL -framework AppKit

UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -Imlx_linux
		MLXFLAGS += $(LINUXMLXFLAGS)
		MLXDIR = mlx_linux
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -Imlx
		MLXFLAGS += $(MACMLXFLAGS)
		MLXDIR =
    endif

INCLUDES = includes

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a

LIBFTFLAGS = -L$(LIBFTDIR) -lft -I$(LIBFTDIR)

MLX = $(MLXDIR)/libmlx_Linux.a

NAME = cub3d

all : $(NAME)

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT) :
				@make -C $(LIBFTDIR) all

$(MLX) :
				@make -C $(MLXDIR)

ifeq ($(UNAME_S),Linux)
    $(NAME): $(MLX)
endif

$(NAME):		$(OBJS) $(INCLUDES)/$(NAME).h $(LIBFT)
				@echo "Creating $(NAME).."
				@echo "Your display variable is $$DISPLAY"
				@git submodule init
				@git submodule update
				$(CC) $(OBJS) -o $@ $(LIBFTFLAGS) $(MLXFLAGS)

bonus : 		${NAME}

clean :
				@echo "Cleaning all .o files.."
				# @make -C mlx_linux clean
				@make -C $(LIBFTDIR) clean
				@rm -rf $(OBJ_DIR)
				
fclean : 		clean
				@echo "Cleaning $(NAME)"
				@make -C $(LIBFTDIR) fclean
                ifeq ($(UNAME_S),Linux)
					@make -C $(MLXDIR) clean
                endif
				@rm -f $(NAME)

re : 			fclean all

run	: 			all
				./cub3d maps/basic_map.cub

.PHONY : all bonus clean fclean re run
