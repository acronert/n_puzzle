# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acronert <acronert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 17:55:24 by acronert          #+#    #+#              #
#    Updated: 2024/01/31 16:42:39 by acronert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
		ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c\
		ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
		ft_putendl_fd.c ft_putnbr_fd.c ft_strcpy.c\
		ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstnew.c\
		printf_types_2.c printf_types.c printf_utils.c printf.c \
		get_next_line.c get_next_line_utils.c \
		ft_free_double_char.c ft_strjoin_three.c ft_strjoin_n.c \
		ft_is_charset.c ft_is_strsep.c ft_arrlen.c
OBJS = ${SRCS:.c=.o}

HEAD = libft.h
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rc

all :	${NAME}

${NAME}: ${OBJS}
	@${AR} ${NAME} ${OBJS}
	@echo " "
	@echo "libft.a created !"

%.o : %.c
	@${CC} ${CFLAGS} -c $<
	@echo "Compiling $@"

clean : 
	@${RM} ${OBJS}
	@echo "Cleaned libft object files"

fclean : clean
	@${RM} ${NAME}
	@echo "Cleaned libft"

re : fclean all

.PHONY : all bonus clean fclean re
