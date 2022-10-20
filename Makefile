# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwan-taj <wwan-taj@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 17:03:19 by kwang             #+#    #+#              #
#    Updated: 2022/10/09 21:46:35 by wwan-taj         ###   ########.fr        #
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
				minimap_utils.c \

OBJ_DIR = obj/

SRC_DIR = src/

OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES) -I/usr/include/ -Imlx_linux -O3
CFLAGS = -I$(INCLUDES) -I/usr/include/ -I$(LIBFTDIR)

LINUXMLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

MACMLXFLAGS = -lmlx -framework OpenGL -framework AppKit

MLXFLAGS :=

UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -Imlx_linux
		MLXFLAGS += $(LINUXMLXFLAGS)
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -Imlx
		MLXFLAGS += $(MACMLXFLAGS)
    endif

INCLUDES = includes

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a

LIBFTFLAGS = -L$(LIBFTDIR) -lft -I$(LIBFTDIR)

MLX = mlx_linux/libmlx_Linux.a

NAME = cub3d

all : $(NAME)

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT) :
				@make -C $(LIBFTDIR) all

$(MLX) :
				@make -C mlx_linux

$(NAME):		$(OBJS) $(INCLUDES)/$(NAME).h $(LIBFT)
				@echo "Creating $(NAME).."
				@echo "Your display variable is $$DISPLAY"
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
				@rm -f $(NAME)

re : 			fclean all

run	: 			all
				./cub3d maps/basic_map.cub

.PHONY : all bonus clean fclean re run
