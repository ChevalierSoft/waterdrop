NAME	= waterdrop #🌊
FLAGS	= #-Wall -Wextra -Werror
GRN     = \033[32;01m
RST     = \033[0m
LIBS	= get_next_line.a
OBJS	= ${SRCS:.c=.o}
SRCS	= ./waterdrop.c \
./verif_cub.c \
./debug.c \
./get_infos.c

all: $(NAME)

$(NAME): gnl $(OBJS)
	@echo "Compiling waterdrop"
	@gcc -O3 -o $(NAME) $(OBJS) $(FLAGS) $(LIBS)

gnl:
	make -C ./get_next_line/
	cp ./get_next_line/get_next_line.a .

%.o: %.c
	@gcc -O3 ${FLAGS} -c -o $@ $<

clean:
	rm $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBS)

re: fclean all

PHONY: fclean all clean re
