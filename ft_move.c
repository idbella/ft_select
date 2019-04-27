/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:56:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/26 22:15:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void ft_move(t_params *params, int c)
{
	t_elem	*elem;

    if (!ft_init_draw(params))
        return ;
    if (c == C_UP && params->rows == 1)
		params->pos--;
	else if (c == C_DOWN && params->rows == 1)
		params->pos++;
	else if (c == ' ')
	{
		elem = (t_elem *)params->selected->content;
		elem->selected = !elem->selected;
		if (elem->selected)
			params->pos++;
		ft_draw(params);
	}
}
