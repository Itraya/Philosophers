# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 10:08:47 by mlagrang          #+#    #+#              #
#    Updated: 2022/02/15 12:11:58 by mlagrang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/secure.c	\
			srcs/lib.c		\
			srcs/init.c		\
			srcs/thread.c	\
			main.c

HEADERS	=	Philo.h

OBJS	= ${SRCS:.c=.o}

NAME	= philo

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=thread -o1

%.o:	%.c	${HEADERS} Makefile
		${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean:
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
