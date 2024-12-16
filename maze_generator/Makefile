# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acronert <acronert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 13:52:54 by alex              #+#    #+#              #
#    Updated: 2024/02/08 17:52:17 by acronert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	maze_generator
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

FILES		=	src/main				\
				src/ft_generate_maze	\
				src/nodes
HEADERS		=	
INCLUDE		=	./include
SRCS		=	$(addsuffix .c, $(FILES))
OBJS		=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS) libft
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) ./include/libft/libft.a

%.o: %.c
	@$(CC) $(FLAGS) -c -I$(INCLUDE) -I./include/libft $< -o $@
	@echo "Compiling $@"
	
libft:
	@make -C include/libft/

clean:
	@rm -rf $(OBJS)
	@make -C include/libft/ clean
	@echo "Cleaned $(NAME) object files"

fclean: clean
	@rm -rf $(NAME)
	@make -C include/libft/ fclean
	@echo "Cleaned $(NAME)"

re: fclean all
