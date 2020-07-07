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
	@echo "Deleting gnl object files\c"
	@/bin/rm -f $(OBJS)
	@echo "\t$(GRN)[OK]$(RST)"

fclean: clean
	@echo "Deleting $(NAME)\c"
	@/bin/rm -f $(NAME)
	@echo "\t$(GRN)[OK]$(RST)"

re: fclean all

PHONY: fclean all clean re
