SRCS		= src/main.c

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
