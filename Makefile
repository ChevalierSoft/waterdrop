NAME	= waterdrop #🌊
FLAGS	= #-Wall -Wextra -Werror
GRN     = \033[32;01m
RST     = \033[0m
LIBS	= get_next_line.a libft.a
OBJS	= ${SRCS:.c=.o}
SRCS	= ./waterdrop.c \
./verif_cub.c \
./array_tools.c \
./meta.c \
./debug.c \
./get_infos.c

all: $(NAME)

$(NAME): gnl lft $(OBJS)
	@echo "Compiling waterdrop \c"
	@gcc -O3 -o $(NAME) $(OBJS) $(FLAGS) $(LIBS)
	@echo "\t\t$(GRN)[OK]$(RST)"

gnl:
	make -C ./get_next_line/
	cp ./get_next_line/get_next_line.a .

lft:
	make -C ./libft/
	cp ./libft/libft.a .

%.o: %.c
	@gcc -O3 ${FLAGS} -c -o $@ $<

clean:
	rm $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBS)
	make fclean -C ./libft
	make fclean -C ./get_next_line

re: fclean all

PHONY: fclean all clean re
