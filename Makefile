# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 16:38:27 by aperol-h          #+#    #+#              #
#    Updated: 2022/05/30 18:59:34 by aoteo-be         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= src/cd.c src/echo.c src/env.c src/exit.c src/export.c src/main.c src/parser.c src/path_find.c src/pwd.c src/unset.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -I ./libft/

IS_BONUS = 0

%.o: %.c
			$(CC) $(CFLAGS) -I./includes $< -c -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} 
			make -C libft/
			${CC} ${CFLAGS} ${OBJS} -L libft -lft -lreadline -o ${NAME}

clean:
			make clean -C libft/
			rm -f ${OBJS}

fclean:		clean
			make fclean -C libft/
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
