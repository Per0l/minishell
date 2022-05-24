SRCS		= src/main.c src/str_utils.c src/mem_utils.c src/ft_split.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address

IS_BONUS = 0

%.o: %.c
			$(CC) $(CFLAGS) -I./includes $< -c -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} 
			${CC} ${CFLAGS} ${OBJS} -lreadline -o ${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
