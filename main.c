/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:54:05 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/26 22:23:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_getsize(t_size *size)
{
	struct winsize win_size;

	ioctl(0, TIOCGWINSZ, &win_size);
	size->width = win_size.ws_col;
	size->height = win_size.ws_row;
}

int		ft_bigelem(t_list *list)
{
	int		bigger;
	t_elem	*elem;
	int		len;

	bigger = 0;
	while (list)
	{
		elem = (t_elem *)list->content;
		len = ft_strlen(elem->name);
		if (len > bigger)
			bigger = len;
		list = list->next;
	}
	return (bigger);
}

int		ft_rows(t_list *list, int count, int width, int height)
{
	int rows;
	int bigelem;

	bigelem = ft_bigelem(list);
	rows = 1;
	if (count > height)
	{
		rows = width / (bigelem + 4);
	}
	return (rows ? rows : 1);
}

void	ft_select(t_params *params, int c)
{
	int		count;

	count = ft_lstcount(params->list);
	if (!(c == C_UP || c == C_DOWN || c == C_LEFT || c == C_RIGHT))
		return ;
	ft_move(params, c);
	if (params->pos > count)
		params->pos = 1;
	else if (params->pos < 1)
		params->pos = count;
	ft_draw(params);
}

int		main(int argc, char **argv)
{
	int			key;
	t_params	*params;

	if (argc < 2)
		exit(0);
	params = &g_params;
	ft_setup(params);
	ft_fill(params, argv + 1);
	key = 0;
	ft_draw(params);
	while (read(0, &key, 3))
	{
		if (key == 127 || key == DELETE_KEY)
		{
			ft_remove(params);
			ft_draw(params);
		}
		else if (key == 27)
			ft_exit(params);
		else if (key == '\n')
			ft_print(params);
		ft_select(params, key);
		key = 0;
	}
	return (0);
}
