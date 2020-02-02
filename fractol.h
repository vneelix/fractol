/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 13:26:28 by vneelix           #+#    #+#             */
/*   Updated: 2020/02/02 14:49:12 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** do not change
*/
# define W 1024
# define H 720
# define T 64

/*
** count iterations
*/
# define ITER 64

/*
** libc
*/
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include <pthread.h>

/*
** remove it
*/
# include <stdio.h>

/*
** structs
*/

typedef void*(*t_func)(void *arg);

typedef struct	s_mlx{
	void		*ptr;
	void		*win;
	void		*img_ptr;
	void		*img_add;
}				t_mlx;

typedef struct	s_complex{
	double		re;
	double		im;
}				t_complex;

typedef	struct	s_fractol
{
	int			set;
	t_mlx		mlx;
	double		scale;
	double		mov_x;
	double		mov_y;
	int			itera;
	t_complex	julia_c;
	int			julia_l;
	double		shift_c;
	t_func		fractol[16];
}				t_fractol;

typedef struct	s_block
{
	__uint32_t	num;
	pthread_t	tid;
	int			x;
	int			y;
	int			x1;
	int			y1;
	t_fractol	*f;
}				t_block;

void			start_pthread(t_block *b);
void			*fractol_init(char *frac);
int				bernstein_color(int *iter, int *itera, double *shift);
void			print_hud(t_fractol *f);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_exit(t_fractol *f, t_block *b);

/*
** mlx_event
*/
int				key_press(int keycode, void *arg);
int				mouse(int keycode, int x, int y, void *arg);
int				mouse_mov(int x, int y, void *arg);

/*
** set
*/
void			*mandelbrot_pthread(void *arg);
void			*mandelbrot_init(void *arg);
void			*julia_pthread(void *arg);
void			*julia_init(void *arg);
void			*multib0_pthread(void *arg);
void			*multib0_init(void *arg);
void			*multib3_pthread(void *arg);
void			*multib3_init(void *arg);
void			*multib5_pthread(void *arg);
void			*multib5_init(void *arg);
void			*multib6_pthread(void *arg);
void			*multib6_init(void *arg);
void			*bship_pthread(void *arg);
void			*bship_init(void *arg);
void			*bird_pthread(void *arg);
void			*bird_init(void *arg);

#endif
