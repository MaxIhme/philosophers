# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 18:09:20 by mrehberg          #+#    #+#              #
#    Updated: 2023/01/24 11:47:13 by mrehberg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRC_DIR := src/

SRC := $(SRC_DIR)philo.c \
	$(SRC_DIR)ft_atoi.c \
	$(SRC_DIR)init.c \
	$(SRC_DIR)error.c \
	$(SRC_DIR)philo_actions.c \
	$(SRC_DIR)utils.c \
	$(SRC_DIR)clean_up.c \
	
OBJS := $(SRC:.c=.o)

CC := gcc

C_FLAGS := -Wall -Wextra -Werror -pthread -g

C_TEST_FLAGS := -Wall -Wextra -g -pthread #-fsanitize=thread #-fsanitize=address

all: $(NAME)

$(NAME): Makefile $(SRC)
	$(CC) $(C_FLAGS) $(SRC) -o $@

phil := 2
die := 401
eat := 200
sleep := 100
must_eat := 10

e: $(NAME)
	./$(NAME) $(phil) $(die) $(eat) $(sleep) $(must_eat)

l: $(NAME)
	leaks --atExit -- ./$(NAME) $(phil) $(die) $(eat) $(sleep) $(must_eat)

v: $(NAME)
	./$(NAME) $(phil) $(die) $(eat) $(sleep) $(must_eat) | pbcopy
#>> log.txt
#| pbcopy

t: $(NAME)
#	./$(NAME) 4 310 200 100 20 >> log.txt
	./$(NAME) $(phil) $(die) $(eat) $(sleep) $(must_eat) | ../tester_anruland/philotester $(phil) $(die) $(must_eat)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f *.out

re: fclean all

.PHONY: all clean fclean re