# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 17:40:50 by gufreire          #+#    #+#              #
#    Updated: 2025/10/23 19:34:53 by gufreire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
#-Wall -Wextra -Werror falta meter nas flags
CFLAGS = -g -pthread
RM = rm -f
ARGS = 3 410 200 200

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Functions diretory
SRC_FILES = forks.c innit.c main.c parsing.c philo_utils.c routine.c time.c
SRC_FUNC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRC = $(SRC_FUNC)

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
		$(RM) -rf $(OBJ_DIR)
		
fclean: clean
		$(RM) $(NAME)

valgrind:
	valgrind ./$(NAME) || true

re: fclean all

debug: CFLAGS += -D DEBUG=1
debug: re
	./$(NAME) $(ARGS)
san: $(OBJ)
		$(CC) $(CFLAGS) -fsanitize=address  $(OBJ) -o $(NAME)

.PHONY: all clean fclean re