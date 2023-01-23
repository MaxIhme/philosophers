# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 18:09:20 by mrehberg          #+#    #+#              #
#    Updated: 2023/01/23 20:12:16 by mrehberg         ###   ########.fr        #
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

C_FLAGS := -Wall -Wextra -Werror -pthread

C_TEST_FLAGS := -Wall -Wextra -g -pthread #-fsanitize=thread #-fsanitize=address

all: $(NAME)

$(NAME): Makefile $(SRC)
	$(CC) $(C_TEST_FLAGS) $(SRC) -o $@

e: $(NAME)
	./$(NAME) 5 800 200 200
#>> log.txt
#| pbcopy

t: $(NAME)
#	./$(NAME) 4 310 200 100 20 >> log.txt
	./$(NAME) 5 800 200 200 7 | ../tester_anruland/philotester 5 800 7

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f *.out

re: fclean all

.PHONY: all clean fclean re