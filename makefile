# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 11:48:55 by benmoham          #+#    #+#              #
#    Updated: 2022/01/26 16:41:58 by benmoham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	childs_process.c		\
				cmd_path.c		\
				ft_split.c 	\
				ft_strncmp.c	\
				pipex.c	\
				ft_strcat.c     \
				ft_strdup.c     \
			
OBJS			= $(SRCS:.c=.o)

NAME			= pipex

CFLAGS			= -Wall -Wextra -Werror -g

RM				= rm -f

CC				= gcc

AR				= ar rcs

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L.

all:			$(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME) 

re:				fclean all


.PHONY:			all clean fclean c.o re 