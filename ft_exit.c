/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:59:03 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/26 21:28:13 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_free(t_params *params)
{
	t_elem		*elem;
	t_list		*lst;

	while (params->list)
	{
		elem = (t_elem *)params->list->content;
		free(elem->name);
		free(elem);
		lst = params->list;
		params->list = params->list->next;
		free(lst);
	}
}

void	ft_exit(t_params *params)
{
	tputs(params->endwindow, 1, ft_put);
	tputs(params->show_cursor, 1, ft_put);
	tcsetattr(0, TCSANOW, &params->term);
	exit(0);
}
