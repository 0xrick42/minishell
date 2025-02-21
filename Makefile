NAME		=	minishell

CC			=	cc
C_FLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP

SRCS_DIR	=	srcs
OBJ_DIR		=	objs
SRCS_NAMES	=	main.c \
				parse/char_utils.c \
				parse/ft_split_quotes.c \
				parse/ft_split_quotes_utils.c \
				parse/ft_split_quotes_utils2.c \
				parse/ft_split_quotes_utils3.c \
				parse/ft_split_quotes_utils4.c \
				parse/ft_split_quotes_utils5.c \
				parse/parse_char.c \
				parse/parsing.c \
				token/check_tokens.c \
				token/create_tokens.c \
				token/create_tokens_utils3.c \
				token/token_utils.c \
				token/token_ops.c \
				token/token_ops2.c \
				token/token_ops3.c \
				exec/cmd_list.c \
				exec/cmd_list_utils.c \
				exec/exec_status.c \
				expand/envar.c \
				expand/expand.c \
				expand/expand_process.c \
				expand/exp_utils.c \
				expand/exp_dollars.c \
				builtins/echo.c \
				builtins/pwd.c \
				builtins/env.c \
				builtins/cd.c \
				builtins/export.c \
				builtins/unset.c \
				builtins/exit.c \
				utils/error.c \
				utils/exit_status.c

OBJS_NAMES	=	$(SRCS_NAMES:.c=.o)
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))
OBJS		=	$(addprefix $(OBJ_DIR)/,$(OBJS_NAMES))

HEADER		=	-Iincludes -Ilibft

LIBFT		=	libft/libft.a

GREEN		=	\033[1;32m
RED			=	\033[1;31m
YELLOW		=	\033[1;33m
ORANGE		=	\033[38;5;214m
PURPLE		=	\033[1;35m
BOLD		:=	\033[1m
RESET		=	\033[0m

SUCCESS		=	[ ✔ ]
ERROR		=	[ ✗ ]
CLEAN		=	[ ♻ ]
REMOVE		=	[ 🗑 ]
REDO		=	[ 🗘 ]

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(C_FLAGS) $(OBJS) $(HEADER) $(LIBFT) -lreadline -o $(NAME) || (echo "\n$(RED) ============ $(ERROR) Linking failed ! ====================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Executable created ! ================================== $(RESET)"

$(LIBFT):
	@make -C libft --no-print-directory

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@ $(HEADER) || (echo "\n$(RED) ============ $(ERROR) Compilation failed ! ================================== $(RESET)\n"; exit 1)
	@echo "$(GREEN) ============ $(SUCCESS) Successful compilation ! ============================== $(RESET)"

clean:
	@make clean -C libft --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW) ============ $(CLEAN) Successful binary & dependances cleaning ! ============ $(RESET)"

fclean: clean
	@make fclean -C libft --no-print-directory
	@rm -rf $(NAME)
	@echo "$(BOLD)$(ORANGE) ============ $(REMOVE) Deleted executable ! ================================== $(RESET)"

re: fclean all
	@echo "$(PURPLE) ============ $(REDO) Redo completed ! ====================================== $(RESET)"

.PHONY: all clean fclean re

-include $(DEPS)