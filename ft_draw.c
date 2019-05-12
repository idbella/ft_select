/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:00:44 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/11 23:26:37 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_helper(t_params *params, t_list *list, t_elem *elem, int i)
{
	if (i == params->pos)
	{
		params->selected = list;
		tputs(params->s_underline, 1, ft_put);
	}
	if (elem->selected)
		tputs(params->reverse_v, 1, ft_put);
	ft_putstr_fd(elem->name, 2);
	if (i == params->pos)
		tputs(params->e_underline, 1, ft_put);
	if (elem->selected)
		tputs(params->stop_v, 1, ft_put);
}

static void	ft_print2(t_params *params)
{
	t_list	*list;
	t_elem	*elem;
	int		i;
	int		counter;

	i = 0;
	counter = 1;
	list = params->list;
	while (list && ++i)
	{
		elem = (t_elem *)list->content;
		ft_helper(params, list, elem, i);
		if (params->columns > 1)
			ft_printpadding(ft_strlen(elem->name), params->bigelem);
		if (counter == params->columns)
		{
			if (list->next)
				ft_putchar_fd('\n', 2);
			counter = 0;
		}
		else
			ft_putstr_fd("  ", 2);
		counter++;
		list = list->next;
	}
}

int			ft_init_draw(t_params *params)
{
	t_size	size;
	int		count;

	params->bigelem = ft_bigelem(params->list);
	ft_getsize(&size);
	count = ft_req_lines(params, size.width);
	params->columns = ft_columns(params->list, count, &size);
	params->height = count / params->columns;
	params->height += (count % params->columns) ? 1 : 0;
	return (params->height > size.height);
}

void		ft_draw(t_params *params)
{
	tputs(params->window, 1, ft_put);
	if (ft_init_draw(params))
	{
		ft_putendl_fd("window is too small", 2);
		return ;
	}
	ft_print2(params);
}
