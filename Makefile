NAME = minishell

SRC_DIR = src
LIBFT_DIR = libft
INC_DIR = includes

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
	$(SRC_DIR)/executor/pipes.c \
	$(SRC_DIR)/executor/redirections.c \
	$(SRC_DIR)/expander/expander.c \
	$(SRC_DIR)/expander/quotes.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/lexer/tokens.c \
	$(SRC_DIR)/parser/parser.c \
	$(SRC_DIR)/parser/utils.c \
	$(SRC_DIR)/signals/signals.c \
	$(SRC_DIR)/utils/error.c \
	$(SRC_DIR)/utils/free.c \
	$(SRC_DIR)/utils/utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

# NAME = minishell

# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -Iincludes

# LIBS = -lreadline

# SRCS = src/main.c
# OBJS = $(SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all
