/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:41:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/21 11:02:20 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_config(t_params *params)
{
	struct termios	termio;

	tcgetattr(0, &termio);
	tcgetattr(0, &params->term);
	termio.c_lflag = ~ICANON & termio.c_lflag;
	termio.c_lflag = ~ECHO & termio.c_lflag;
	tcsetattr(0, TCSANOW, &termio);
}

void	ft_setup2(t_params *params)
{
	char			*term;
	char			buff[2048];

	term = getenv("TERM");
	tgetent(buff, term);
	ft_config(params);
}

void	setup(void)
{
	int				pos[2];

	g_params = (t_params *)malloc(sizeof(t_params));
	ft_setup2(g_params);
	g_params->pos = 1;
	g_params->selected = NULL;
	g_params->delete = tgetstr("dl", NULL);
	g_params->mv_up = tgetstr("up", NULL);
	g_params->mv_left = tgetstr("le", NULL);
	g_params->mv_down = tgetstr("do", NULL);
	g_params->mv_right = tgetstr("nd", NULL);
	g_params->reverse_v = tgetstr("mr", NULL);
	g_params->stop_v = tgetstr("me", NULL);
	g_params->window = tgetstr("ti", NULL);
	g_params->endwindow = tgetstr("ti", NULL);
	g_params->s_underline = tgetstr("us", NULL);
	g_params->e_underline = tgetstr("ue", NULL);
	g_params->hide_cursor = tgetstr("vi", NULL);
	g_params->show_cursor = tgetstr("ve", NULL);
}
