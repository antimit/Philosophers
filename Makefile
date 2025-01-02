# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lpthread

# Executable name
NAME = philosophers

# Source files and objects
SRCS = dinner.c \
       init.c \
       main.c \
       safe_functions.c \
       write.c \
       getters_setters.c \
       parsing.c \
       synchro_utilc.c \
       utils.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
