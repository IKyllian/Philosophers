NAME = philo

HEADER = include/philosophers.h
SRCS =  main.c \
		free.c \
		parsing.c \
		init.c \
		utils.c \
		action.c \
		philo.c

OBJS = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wextra -Werror -Wall
RM = rm -f

all : $(NAME)
 
%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(HEADER)
		$(CC) $(FLAGS) -o $@ $(OBJS)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean re all run