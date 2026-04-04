NAME = minishell

SRC_DIR = src
LIBFT_DIR = libft
INC_DIR = includes
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
DEP_DIR = $(BUILD_DIR)/dep

READLINE = -lreadline

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/builtins/cd.c \
	$(SRC_DIR)/builtins/echo.c \
	$(SRC_DIR)/builtins/env.c \
	$(SRC_DIR)/builtins/exit.c \
	$(SRC_DIR)/builtins/export.c \
	$(SRC_DIR)/builtins/pwd.c \
	$(SRC_DIR)/builtins/unset.c \
	$(SRC_DIR)/env/env_init.c \
	$(SRC_DIR)/env/env_utils.c \
	$(SRC_DIR)/executor/executor.c \
	$(SRC_DIR)/executor/exec.utils.c \
	$(SRC_DIR)/executor/pipes.c \
	$(SRC_DIR)/executor/redirections.c \
	$(SRC_DIR)/executor/redir.utils.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/lexer/tokens.c \
	$(SRC_DIR)/lexer/handle_dollar.c \
	$(SRC_DIR)/lexer/handle_word.c \
	$(SRC_DIR)/lexer/validate_line.c \
	$(SRC_DIR)/parser/parser.c \
	$(SRC_DIR)/parser/parser_redir.c \
	$(SRC_DIR)/parser/parser_arg.c \
	$(SRC_DIR)/parser/validate_syntax.c \
	$(SRC_DIR)/signals/signals.c \
	$(SRC_DIR)/utils/error.c \
	$(SRC_DIR)/utils/free.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/builtin_utils.c \
	$(SRC_DIR)/executor/pipes_utils.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
