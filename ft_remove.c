/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 19:56:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/28 15:41:28 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_delete(t_params *params, t_list *list, t_list **new, int i)
{
	t_elem	*elem;
	t_list	*node;

	if (i == params->pos)
	{
		params->pos = params->pos > 1 ? params->pos - 1 : 1;
		elem = (t_elem *)list->content;
		free(elem->name);
		free(elem);
	}
	else
	{
		node = ft_lstnew(NULL, 0);
		node->content = list->content;
		ft_lstadd(new, node);
	}
}

void		ft_remove(t_params *params)
{
	t_list	*list;
	t_list	*new;
	t_list	*tmp;
	int		i;

	i = 1;
	new = NULL;
	list = params->list;
	if (ft_init_draw(params))
		return ;
	while (list)
	{
		ft_delete(params, list, &new, i);
		i++;
		tmp = list;
		list = list->next;
		free(tmp);
	}
	if (!new)
		ft_exit(params);
	params->list = new;
}
