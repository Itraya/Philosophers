# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 10:08:47 by mlagrang          #+#    #+#              #
#    Updated: 2022/02/14 16:22:50 by mlagrang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c

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
