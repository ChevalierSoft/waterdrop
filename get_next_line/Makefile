NAME = get_next_line.a
GRN     = \033[32;01m
RST     = \033[0m
FLAGS	= -Wall -Wextra -Werror
OBJS    = ${SRCS:.c=.o}
SRCS	= ./get_next_line.c ./get_next_line_utils.c 

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "Compiling get_next_line.a\c"
	@ar -rcs $(NAME) $(OBJS)
	@echo "\t\t$(GRN)[OK]$(RST)"

.o: %.c
	@gcc ${FLAGS} -c -o $@ $< get_next_line.h

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

PHONY: fclean all clean re
