# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 15:42:19 by sid-bell          #+#    #+#              #
#    Updated: 2019/04/21 11:47:00 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_select
FLAGS= -Wall -Wextra -Werror
all:$(NAME)
$(NAME):
		make -C libft
		@gcc $(FLAGS) -c *.c
		@gcc $(FLAGS) *.o libft/libft.a -o $(NAME) -l termcap
clean:
		make -C libft/ clean
		@rm -rf *.o
fclean: clean
		make -C libft/ fclean
		@rm -rf $(NAME)
re:fclean
		@make all
		make clean