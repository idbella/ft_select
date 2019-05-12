/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:03:42 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/05 19:43:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_print(t_params *params)
{
	t_list	*list;
	t_elem	*elem;
	int		prev;

	list = params->list;
	tputs(params->show_cursor, 1, ft_put);
	tputs(params->endwindow, 1, ft_put);
	tcsetattr(0, TCSANOW, &params->term);
	prev = 0;
	while (list)
	{
		elem = (t_elem *)list->content;
		if (elem->selected)
		{
			if (prev)
				ft_putchar(' ');
			ft_putstr(elem->name);
			prev = 1;
		}
		list = list->next;
	}
	ft_free(params);
	exit(0);
}

int		ft_put(int c)
{
	ft_putchar_fd(c, 2);
	return (c);
}

void	ft_printpadding(int lenght, int biggelem)
{
	while (biggelem > lenght)
	{
		ft_putchar_fd(' ', 2);
		biggelem--;
	}
}
