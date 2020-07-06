NAME	= waterdrop #🌊
FLAGS	= #-Wall -Wextra -Werror
GRN     = \033[32;01m
RST     = \033[0m
OBJS	= ${SRCS:.c=.o}
SRCS	= ./waterdrop.c \
./verif_cub.c \
./debug.c \
./get_next_line.c \
./get_infos.c

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling waterdrop"
	@gcc -O3 -o $(NAME) $(OBJS) $(FLAGS)

%.o: %.c
	@gcc -O3 ${FLAGS} -c -o $@ $< -I ./waterdrop.h

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

PHONY: fclean all clean re
