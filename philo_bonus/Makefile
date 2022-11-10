# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 09:13:00 by jmanet            #+#    #+#              #
#    Updated: 2022/11/10 17:17:35 by jmanet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/philo.c srcs/utils.c srcs/atoi.c

INCLUDES =

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

LIBS = -pthread

.c.o:
	${CC} -I ${INCLUDES} ${FLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${SRCS} ${LIBS} -I ${INCLUDES} ${FLAGS} -o ${NAME}

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all
