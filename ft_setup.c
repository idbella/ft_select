/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:41:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/27 12:02:46 by sid-bell         ###   ########.fr       */
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

char	*ft_setup2(t_params *params)
{
	char			*term;
	char			buff[2048];

	signal(SIGWINCH, ft_catch);
	signal(SIGCONT, ft_catch);
	signal(SIGINT, ft_catch);
	if (!(term = getenv("TERM")))
	{
		ft_printf_fd(2, "TERM variable not set");
		exit(1);
	}
	if (!(tgetent(buff, term)))
	{
		ft_printf_fd(2, "cannot get Terminal: %s capabilities\n", term);
		exit(0);
	}
	ft_config(params);
	return (term);
}

void	ft_setup(t_params *params)
{
	char *term;

	term = ft_setup2(params);
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
		ft_printf_fd(2, "cannot get Terminal: %s capabilities\n", term);
		exit(0);
	}
	tputs(params->hide_cursor, 1, ft_put);
}

void	ft_fill(t_params *params, char **argv)
{
	t_list *lst;
	t_elem *elem;

	params->list = NULL;
	while (*argv)
	{
		elem = (t_elem *)malloc(sizeof(t_elem));
		elem->name = ft_strdup(*argv);
		elem->selected = 0;
		lst = ft_lstnew(NULL, 0);
		lst->content = elem;
		ft_lstadd(&params->list, lst);
		argv++;
	}
	params->list = ft_lstrev(params->list);
}
