NAME	= waterdrop #🌊
FLAGS	= -Wall -Wextra -Werror
GRN     = \033[32;01m
CYN		= \x1B[36;01m
RST     = \033[0m
LIBS	= libft.a
OBJS	= ${SRCS:.c=.o}
SRCS	= ./waterdrop.c \
./main.c \
./array_tools.c \
./meta.c \
./debug.c \
./get_infos.c \
./intel.c \
./quit.c

all: $(NAME)

$(NAME): lft $(OBJS)
	@echo "\rCompiling waterdrop 🌊 \c"
	@gcc -O3 -o $(NAME) $(OBJS) $(FLAGS) $(LIBS)
	@echo "\t\t$(CYN)[OK]$(RST)"

lft:
	@echo "Making and moving libft"
	@make -C ./libft/
	@cp ./libft/libft.a .

%.o: %.c
	@echo "\rmaking $@\c"
	@gcc -O3 ${FLAGS} -c -o $@ $<
	@echo " $(CYN)[OK]$(RST)\c"
	@echo "\r                                  \c"

clean:
	@echo "removing objects \c"
	@rm $(OBJS)
	@echo "\t\t$(GRN)[OK]$(RST)"

fclean: clean
	@echo "removing $(NAME) \c"
	@rm -f $(NAME)
	@echo "\t\t$(CYN)[OK]$(RST)"
	@rm -f $(LIBS)
	@make fclean -C ./libft

re: fclean all

PHONY: fclean all clean re
