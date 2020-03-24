
SRC_P = ./src/
OBJ_P = ./obj/
INC_P = ./inc/
NAME = fractol
MODE = release
CC = clang
CFLAGS = -c -Wall -Wextra -Werror -O2 -I$(INC_P)
DFLAGS = -c -g -O0 -I$(INC_P)
LFLAGS = -lm -lSDL2 -lOpenCL -o $(NAME)
SRC = $(wildcard $(SRC_P)*.c)
OBJ = $(SRC:$(SRC_P)%.c=$(OBJ_P)%.o)
INC = $(wildcard $(INC_P)*.h)

.PHONY: all clean fclean re

$(OBJ_P)%.o: $(SRC_P)%.c $(INC)
ifeq ($(MODE), release)
	$(CC) $(CFLAGS) $< -o $@
else
	$(CC) $(DFLAGS) $< -o $@
endif

$(NAME): $(OBJ)
	$(CC) -Wall -Wextra -Werror $(OBJ) $(LFLAGS)

debug:
	$(MAKE) MODE=debug

all: $(NAME)

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all