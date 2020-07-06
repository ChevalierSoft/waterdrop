NAME	= waterdrop #🌊
FLAGS	= #-Wall -Wextra -Werror
GRN     = \033[32;01m
RST     = \033[0m
SRCS	= ./waterdrop.c \
./verif_cub.c \
./debug.c \
get_next_line.c \
get_infos.c

all: $(NAME)

$(NAME) :
	@echo "Compiling waterdrop"
	@gcc -O3 -o $(NAME) $(SRCS) $(FLAGS)