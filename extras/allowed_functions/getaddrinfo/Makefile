NAME = showip
SRCS = showip.c
CC = clang
CFLAGS += -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean re
