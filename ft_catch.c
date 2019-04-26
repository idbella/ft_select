/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:26:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/26 22:54:35 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_catch(int sig)
{
	if (sig == SIGCONT)
		ft_config(&g_params);
	if (sig == SIGINT)
		ft_exit(&g_params);
	ft_draw(&g_params);
}
