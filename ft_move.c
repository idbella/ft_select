/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:56:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/27 20:41:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_move_up(t_params *params, int count)
{
	int old_pos;

	if (params->rows == 1)
		params->pos--;
	else
	{
		old_pos = params->pos;
		params->pos -= params->rows;
		if (params->pos <= 0 && old_pos != 1)
		{
			params->pos = ((params->height - 1) * params->rows) + old_pos - 1;
			if (params->pos > count)
				params->pos -= params->rows;
		}
		else if (old_pos == 1)
			params->pos = (count / params->rows) * params->rows;
	}
}

static void	ft_move_down(t_params *params, int count)
{
	int old_pos;

	if (params->rows == 1)
		params->pos++;
	else
	{
		old_pos = params->pos;
		params->pos += params->rows;
		if (params->pos > count)
		{
			params->pos = params->pos % params->rows + 1;
		}
	}
}

static void	ft_move_left(t_params *params)
{
	if (params->rows > 1)
		params->pos--;
}

static void	ft_move_right(t_params *params)
{
	if (params->rows > 1)
		params->pos++;
}

void		ft_move(t_params *params, int c, int count)
{
	t_elem	*elem;

	if (ft_init_draw(params))
		return ;
	if (c == C_UP)
		ft_move_up(params, count);
	else if (c == C_DOWN)
		ft_move_down(params, count);
	else if (c == C_RIGHT)
		ft_move_right(params);
	else if (c == C_LEFT)
		ft_move_left(params);
	else if (c == ' ')
	{
		elem = (t_elem *)params->selected->content;
		elem->selected = !elem->selected;
		if (elem->selected)
			params->pos++;
		ft_draw(params);
	}
}
