NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_isalpha \
	ft_isdigit \
	ft_isalnum \
	ft_isascii \
	ft_isprint \
	ft_strlen \
	ft_memset \
	ft_bzero \
	ft_memcpy \
	ft_memmove \
	ft_strlcpy \
	ft_strlcat \
	ft_toupper \
	ft_tolower \
	ft_strchr \
	ft_strrchr \
	ft_strncmp \
	ft_memchr \
	ft_memcmp \
	ft_strnstr \
	ft_atoi \
	ft_calloc \
	ft_strdup \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_split \
	ft_itoa \
	ft_strmapi \
	ft_striteri \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd \
	get_next_line_utils \
	get_next_line \
	ft_printf/ft_printf \
 	ft_printf/ft_utoa_hex_ulong \
	ft_printf/ft_utoa_hex \
	ft_printf/ft_utoa \
	ft_printf/handle_pointer \
	ft_printf/handle_types \
	ft_printf/process_format
SRCS := $(addsuffix .c, $(SRCS))
OBJS := $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $@ $^

all: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
