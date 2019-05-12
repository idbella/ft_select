/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:26:27 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/11 22:55:34 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_reset(t_params *params)
{
	tputs(params->endwindow, 1, ft_put);
	tputs(params->show_cursor, 1, ft_put);
	tcsetattr(0, TCSANOW, &params->term);
}

void		ft_catch_to_cleanup(int sig)
{
	if (sig != SIGTTIN && sig != SIGTTOU)
	{
		ft_free(&g_params);
		ft_reset(&g_params);
		exit(0);
	}
}

void		ft_catch_sig_cont(int sig)
{
	if (sig == SIGCONT)
	{
		signal(SIGTSTP, &ft_catch_sig_stp);
		ft_config(&g_params);
		tputs(g_params.hide_cursor, 1, ft_put);
		ft_draw(&g_params);
	}
}

void		ft_catch_sigwin_change(int sig)
{
	if (sig == SIGWINCH)
		ft_draw(&g_params);
}

void		ft_catch_sig_stp(int sig)
{
	if (sig)
	{
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
		ft_reset(&g_params);
	}
}
