# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 11:16:14 by ybouyzem          #+#    #+#              #
#    Updated: 2024/11/11 07:01:28 by ybouyzem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

HEADER = philosophers.h

FILES = main.c philosophers.c philosophers_utils.c initialization.c\
		monitor.c \

CFLAGS =  -Wall -Wextra -Werror 

OBJECTFILES = $(FILES:.c=.o)
PROGRAM = philo

%.o: %.c $(HEADER)
	cc $(CFLAGS) -o $@ -c $<
 
$(PROGRAM): $(OBJECTFILES)
	cc $(OBJECTFILES) -o $(PROGRAM)

all: $(PROGRAM)

clean:
	rm -f $(OBJECTFILES)

fclean: clean
	rm -f $(PROGRAM)

re: fclean all

.PHONY: clean