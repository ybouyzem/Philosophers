# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 11:16:14 by ybouyzem          #+#    #+#              #
#    Updated: 2024/11/22 19:13:32 by ybouyzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

HEADER = philosophers.h

FILES = main.c philosophers.c utils.c initialization.c\
		monitor.c malloc.c\

CFLAGS =  -Wall -Wextra -Werror  #-fsanitize=thread -g 

OBJECTFILES = $(FILES:.c=.o)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJECTFILES)
	cc $(OBJECTFILES) $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJECTFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean