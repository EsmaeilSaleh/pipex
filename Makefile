NAME := pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -Iinclude -I../libft

LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a

SRCS := \
	src/main.c \
	src/path.c \
	src/parse.c \
	src/utils.c

OBJS := $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

%.o: %.c include/pipex.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
