/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:54:05 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/21 11:24:44 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int ft_put(int c)
{
	ft_putchar_fd(c, g_params->fd_out);
	return (c);
}

void ft_fill(t_params *params, char **argv)
{
	t_list *lst;
	t_elem *elem;

	params->list = NULL;
	while (*argv)
	{
		elem = (t_elem *)malloc(sizeof(t_elem));
		elem->name = ft_strdup(*argv);
		lst = ft_lstnew(NULL, 0);
		lst->content = elem;
		ft_lstadd(&params->list, lst);
		argv++;
	}
	params->list = ft_lstrev(params->list);
}

void	ft_getsize(int *width, int *height)
{
	struct winsize size;

	ioctl(0, TIOCGWINSZ, &size);
	*width = size.ws_col;
	*height = size.ws_row;
}

void ft_exit(t_params *params)
{
	tputs(params->endwindow, 1, ft_put);
	tputs(g_params->show_cursor, 1, ft_put);
	tcsetattr(0, TCSANOW, &params->term);
	exit(0);
}

void ft_print(t_params *params)
{
	t_list *list;
	t_elem *elem;
	int		prev;

	list = params->list;
	tputs(g_params->show_cursor, 1, ft_put);
	tputs(params->endwindow, 1, ft_put);
	prev = 0;
	while (list)
	{
		elem = (t_elem *)list->content;
		if (elem->selected)
		{
			if (prev)
				ft_printf_fd(1, " ");
			ft_printf_fd(1, "%s", elem->name);
			prev = 1;
		}
		list = list->next;
	}
	exit(0);
}

int ft_bigelem(t_list *list)
{
	int		bigger;
	t_elem	*elem;

	bigger = 0;
	while (list)
	{
		elem = (t_elem *)list->content;
		if (ft_strlen(elem->name) > bigger)
			bigger = ft_strlen(elem->name);
		list = list->next;
	}
	return (bigger);
}

int ft_rows(t_list *list,int count, int width, int height)
{
	int rows;
	int bigelem;

	bigelem = ft_bigelem(list);
	rows = 1;
	if (count > height)
	{
		rows = width / (bigelem + 4);
	}
	return (rows);
}

void ft_printpadding(int lenght, int biggelem)
{
	while (biggelem > lenght)
	{
		ft_putchar_fd(' ', g_params->fd_out);
		biggelem--;
	}
}

void ft_darw(t_params *params)
{
	int width;
	int height;
	int count;
	int rows;
	t_elem *elem;
	t_list *list;
	int bigelem;

	bigelem = ft_bigelem(params->list);
	count = ft_lstcount(params->list);
	ft_getsize(&width, &height);
	rows = ft_rows(params->list, count, width, height);
	list = params->list;
	int counter = 1;
	tputs(params->endwindow, 1, ft_put);
	tputs(g_params->window, 1, ft_put);
	tputs(g_params->hide_cursor, 1, ft_put);
	int i = 1;
	while (list)
	{
		elem = (t_elem *)list->content;
		if (i == params->pos)
		{
			params->selected = list;
			tputs(params->s_underline, 1, ft_put);
		}
		if (elem->selected)
			tputs(params->reverse_v, 1, ft_put);
		ft_printf_fd(params->fd_out, "%s", elem->name);
		if (i == params->pos)
			tputs(params->e_underline, 1, ft_put);
		if (elem->selected)
			tputs(params->stop_v, 1, ft_put);
		ft_printpadding(ft_strlen(elem->name), bigelem);
		if (counter == rows)
		{
			if (list->next)
				ft_printf_fd(params->fd_out, "\n");
			counter = 0;
		}
		else
			ft_printf_fd(params->fd_out, "    ");
		counter++;
		list = list->next;
		i++;
	}
}

void ft_select(t_params *params, int c)
{
	int count;

	count = ft_lstcount(params->list);
	if (c == C_LEFT)
		params->pos--;
	else if (c == C_RIGHT)
		params->pos++;
	else if (c == C_DOWN)
	{

	}
	else
		return ;
	if (params->pos > count)
		params->pos = 1;
	else if (params->pos < 1)
		params->pos = count;
	ft_darw(params);
}

void ft_catch(int sig)
{
	if (sig == SIGCONT)
		ft_config(g_params);
	ft_darw(g_params);
}

int main(int argc, char **argv)
{
	t_list		*list;
	t_elem		*elem;
	
	signal(SIGWINCH, ft_catch);
	signal(SIGCONT, ft_catch);
	setup();
	if (!isatty(1))
	{
		g_params->fd_out = open("/dev/tty", O_WRONLY);
		g_params->fd_in = open("/dev/tty", O_RDONLY);
	}
	else
	{
		g_params->fd_in = 0;
		g_params->fd_out = 1;
	}
	ft_fill(g_params, argv + 1);
	int key = 0;
	ft_printf_fd(g_params->fd_out, "%d - %d\n", g_params->fd_in, g_params->fd_out);
	ft_darw(g_params);
	while (read(0, &key, 3))
	{
		if (key == 27)
			ft_exit(g_params);
		if (key == ' ')
		{
			elem = (t_elem *)g_params->selected->content;
			elem->selected = !elem->selected;
			if (elem->selected)
				g_params->pos++;
			ft_darw(g_params);
		}
		if (key == '\n')
			ft_print(g_params);
		ft_select(g_params, key);
		key = 0;
	}
	return (0);
}