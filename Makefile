# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/03 18:03:55 by vneelix           #+#    #+#              #
#    Updated: 2020/02/02 14:51:17 by vneelix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = ./set

NAME = fractol

OBJ = main.o fractol_init.o mlx_event.o mandelbrot.o julia.o ft_strcmp.o multib3.o multib5.o multib6.o bship.o bird.o multib_other.o

INCL = fractol.h

MLX = libmlx.a

INCL_PATH = ./

CFLAGS = -Wall -Wextra -Werror -I./ -O2 -c

LFLAGS = -lm -lmlx -lpthread -framework OpenGL -framework AppKit -o $(NAME)

.PHONY: all clean fclean re

%.o: %.c $(INCL)
	gcc $(CFLAGS) $<

$(NAME): $(OBJ)
	$(MAKE) -C ./mlx/minilibx_macos_sierra
	mv ./mlx/minilibx_macos_sierra/libmlx.a ./
	$(MAKE) clean -C ./mlx/minilibx_macos_sierra
	gcc -Wall -Wextra -Werror $^ $(LFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
