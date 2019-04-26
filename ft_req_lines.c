/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_req_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:16:29 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/26 21:30:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	ft_req_lines(t_params *params, int width)
{
	t_elem	*elem;
	t_list	*list;
	int		lines;
	int		len;

	list = params->list;
	lines = 0;
	while (list)
	{
		elem = (t_elem *)list->content;
		len = ft_strlen(elem->name);
		if (len > width)
		{
			lines += len / width;
			if (len % width)
				lines++;
		}
		else
			lines++;
		list = list->next;
	}
	return (lines);
}
