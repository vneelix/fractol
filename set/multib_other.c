/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multib_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:11:41 by vneelix           #+#    #+#             */
/*   Updated: 2020/01/07 20:56:58 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		*multib0_init(void *arg)
{
	t_fractol *f;

	f = arg;
	f->scale = 250;
	f->mov_x = 2.04;
	f->mov_y = 1.4;
	f->itera = ITER;
	f->shift_c = 0;
	return (NULL);
}

static void	multib0_calc(t_complex *c, int *iter, int *itera)
{
	t_complex	z;
	t_complex	tmp;
	double		d;

	z.re = c->re;
	z.im = c->im;
	*iter = 0;
	while (*iter < *itera && (z.re * z.re + z.im * z.im) <= 4)
	{
		tmp = z;
		d = tmp.re * tmp.re * tmp.re * tmp.re
			+ 2 * tmp.re * tmp.re * tmp.im * tmp.im
				+ tmp.im * tmp.im * tmp.im * tmp.im;
		if (d == 0)
			break ;
		z.re = (tmp.re * tmp.re - tmp.im * tmp.im) / d;
		z.im = -2 * tmp.re * tmp.im / d;
		z.re += c->re;
		z.im += c->im;
		*iter += 1;
	}
}

void		*multib0_pthread(void *arg)
{
	int			iter;
	t_block		*b;
	t_complex	c;

	b = arg;
	while (b->y < b->y1)
	{
		c.im = b->y / b->f->scale - b->f->mov_y;
		while (b->x < b->x1)
		{
			c.re = b->x / b->f->scale - b->f->mov_x;
			multib0_calc(&c, &iter, &(b->f->itera));
			((int*)(b->f->mlx.img_add))[b->x + W * b->y] =
				bernstein_color(&iter, &(b->f->itera), &(b->f->shift_c));
			b->x += 1;
		}
		b->x = b->num % 8 * 128;
		b->y += 1;
	}
	b->y = b->num / 8 * 90;
	pthread_exit(NULL);
}
