/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:41:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/27 22:20:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_config(t_params *params)
{
	struct termios	termio;

	tcgetattr(0, &termio);
	tcgetattr(0, &params->term);
	termio.c_lflag = ~ICANON & termio.c_lflag;
	termio.c_lflag = ~ECHO & termio.c_lflag;
	tcsetattr(0, TCSANOW, &termio);
}

static void	ft_setup2(t_params *params)
{
	char			*term;
	char			buff[2048];
	int				sig;

	sig = 1;
	while (sig <= 32)
	{
		if (sig != SIGCHLD && sig != SIGIO && sig != SIGINFO && sig != SIGURG)
			signal(sig, ft_catch);
		sig++;
	}
	if (!(term = getenv("TERM")))
	{
		ft_putendl_fd("TERM variable not set", 2);
		exit(1);
	}
	if (!(tgetent(buff, term)))
	{
		ft_putendl_fd("cannot find Terminal Database", 2);
		exit(0);
	}
	ft_config(params);
}

void		ft_setup(t_params *params)
{
	ft_setup2(params);
	params->pos = 1;
	params->selected = NULL;
	params->reverse_v = tgetstr("mr", NULL);
	params->stop_v = tgetstr("me", NULL);
	params->window = tgetstr("ti", NULL);
	params->endwindow = tgetstr("te", NULL);
	params->s_underline = tgetstr("us", NULL);
	params->e_underline = tgetstr("ue", NULL);
	params->hide_cursor = tgetstr("vi", NULL);
	params->show_cursor = tgetstr("ve", NULL);
	params->clear = tgetstr("cl", NULL);
	if (!(params->reverse_v && params->stop_v
		&& params->window && params->endwindow
		&& params->s_underline && params->e_underline
		&& params->hide_cursor && params->show_cursor))
	{
		ft_putendl_fd("cannot get Terminal Capabilities", 2);
		exit(1);
	}
	tputs(params->hide_cursor, 1, ft_put);
}

void		ft_fill(t_params *params, char **argv, int argc)
{
	t_list *lst;
	t_elem *elem;

	params->list = NULL;
	while (argc > 0)
	{
		elem = (t_elem *)malloc(sizeof(t_elem));
		elem->name = ft_strdup(argv[argc]);
		elem->selected = 0;
		lst = ft_lstnew(NULL, 0);
		lst->content = elem;
		ft_lstadd(&params->list, lst);
		argc--;
	}
}
