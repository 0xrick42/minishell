CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
INCLUDES = -Ilibft
SRCS = parsing.c \
token_utils.c \
tokens.c \
create_tokens.c \
check_tokens.c \
char_utils.c 
NAME = minishell
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIB_FLAGS = -Ilibft -L./libft -lft
 
all: $(LIBFT_LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
 
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS)  -o $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean re