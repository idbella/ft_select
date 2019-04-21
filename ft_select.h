/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:54:17 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/21 11:02:28 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "libft/libft.h"
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# define C_UP 4283163
# define C_DOWN 4348699
# define C_RIGHT 4414235
# define C_LEFT 4479771

typedef struct  s_elem
{
    char    *name;
    char    selected : 1;
}               t_elem;
typedef struct termios t_termios;
typedef struct  s_params
{
    int         fd_in;
    int         fd_out;
    int         pos;
    int         bigelem;
    int         rows;
    int         width;
    int         height;
    t_list      *list;
    char	    *delete;
	char	    *mv_up;
	char	    *mv_left;
	char	    *mv_right;
	char	    *mv_down;
    char        *s_underline;
    char        *e_underline;
	char	    *reverse_v;
	char        *stop_v;
    char        *window;
    char        *endwindow;
    char        *hide_cursor;
    char        *show_cursor;
    t_termios   term;
    t_list      *selected;
}               t_params;
t_params    *g_params;
void	setup();
void	ft_config(t_params *params);
#endif