/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:26:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/27 22:38:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_reset(t_params *params)
{
	tputs(params->endwindow, 1, ft_put);
	tputs(params->show_cursor, 1, ft_put);
	tcsetattr(0, TCSANOW, &params->term);
}

void		ft_catch(int sig)
{
	if (sig == SIGCONT)
	{
		signal(SIGTSTP, &ft_catch);
		ft_config(&g_params);
		tputs(g_params.hide_cursor, 1, ft_put);
	}
	else if (sig == SIGTSTP)
	{
		ft_reset(&g_params);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
	}
	else if (sig != SIGTTIN && sig != SIGTTOU && sig != SIGWINCH)
	{
		ft_free(&g_params);
		ft_reset(&g_params);
		exit(0);
	}
	if (sig != SIGTSTP)
		ft_draw(&g_params);
}
