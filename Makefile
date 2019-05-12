# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 15:42:19 by sid-bell          #+#    #+#              #
#    Updated: 2019/05/11 20:43:32 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_select
FLAGS= -Wall -Wextra -Werror
O_FILES=ft_catch.o ft_draw.o ft_exit.o ft_move.o ft_print.o ft_remove.o ft_req_lines.o ft_setup.o main.o
C_FILES=ft_catch.c ft_draw.c ft_exit.c ft_move.c ft_print.c ft_remove.c ft_req_lines.c ft_setup.c main.c
all:$(NAME)
$(NAME):
		make -C libft
		@gcc $(FLAGS) -c $(C_FILES)
		gcc $(FLAGS) $(O_FILES) libft/libft.a -o $(NAME) -l termcap
clean:
		make -C libft/ clean
		@rm -rf $(O_FILES)
fclean: clean
		@make -C libft/ fclean
		@rm -rf $(NAME)
re:fclean
		@make all
