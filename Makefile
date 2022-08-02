# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 16:38:27 by aperol-h          #+#    #+#              #
#    Updated: 2022/08/02 19:13:59 by aperol-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=  src/main.c src/cd.c src/echo.c src/env.c src/exit.c src/export.c src/parser.c src/parse_utils.c src/path_find.c src/pwd.c src/unset.c src/utils.c src/executer.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

LIBFT 		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -I ./libft/ -g #-fsanitize=address 

IS_BONUS = 0

%.o: %.c
			$(CC) $(CFLAGS) -I./includes $< -c -o ${<:.c=.o}

all:		${NAME}


${NAME}:	${OBJS}
			make -C libft/
			make bonus -C libft/
			${CC} ${CFLAGS} ${OBJS} -L libft -lft -lreadline -o ${NAME}

clean:
			make clean -C libft/
			rm -f ${OBJS}

fclean:		clean
			make fclean -C libft/
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
