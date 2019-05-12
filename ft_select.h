/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:54:17 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/11 22:32:52 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "libft/libft.h"
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# define C_UP 4283163
# define C_DOWN 4348699
# define C_RIGHT 4414235
# define C_LEFT 4479771
# define DELETE_KEY 2117294875

typedef struct			s_elem
{
	char	*name;
	char	selected:1;
}						t_elem;
typedef struct termios	t_termios;
typedef struct			s_params
{
	int			pos;
	int			bigelem;
	int			columns;
	int			width;
	int			height;
	t_list		*list;
	char		*s_underline;
	char		*e_underline;
	char		*reverse_v;
	char		*stop_v;
	char		*window;
	char		*endwindow;
	char		*hide_cursor;
	char		*show_cursor;
	char		*clear;
	t_termios	term;
	t_list		*selected;
}						t_params;
t_params				g_params;
typedef struct			s_size
{
	int		width;
	int		height;
}						t_size;
void					ft_setup(t_params *params);
void					ft_config(t_params *params);
void					ft_remove(t_params *params);
void					ft_exit(t_params *params);
int						ft_put(int c);
int						ft_req_lines(t_params *params, int width);
void					ft_printpadding(int lenght, int biggelem);
int						ft_columns(t_list *list, int count, t_size *size);
int						ft_bigelem(t_list *list);
void					ft_getsize(t_size *size);
void					ft_draw(t_params *params);
void					ft_print(t_params *params);
void					ft_fill(t_params *params, char **argv);
void					ft_free(t_params *params);
void					ft_move(t_params *params, int key, int count);
int						ft_init_draw(t_params *params);
void					ft_just_catch(int sig);
void					ft_catch_to_cleanup(int sig);
void					ft_catch_sig_cont(int sig);
void					ft_catch_sig_stp(int sig);
void					ft_catch_sigwin_change(int sig);
#endif
