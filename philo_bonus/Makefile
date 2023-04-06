NAME = philo_bonus

CC = cc -Wall -Wextra -Werror
RM = rm -f

SRC = philosophers.c check_error.c check_error1.c data.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all