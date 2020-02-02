/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bship.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 16:11:41 by vneelix           #+#    #+#             */
/*   Updated: 2020/01/07 18:53:48 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		*bship_init(void *arg)
{
	t_fractol *f;

	f = arg;
	f->scale = 250;
	f->mov_x = 2.5;
	f->mov_y = 2;
	f->itera = ITER;
	f->shift_c = 0;
	return (NULL);
}

static void	bship_calc(t_complex *c, int *iter, int *itera)
{
	t_complex	z;
	t_complex	tmp;

	z.re = c->re;
	z.im = c->im;
	*iter = 0;
	while (*iter < *itera && (z.re * z.re + z.im * z.im) <= 4)
	{
		tmp = z;
		z.re = tmp.re * tmp.re - tmp.im * tmp.im;
		z.im = fabs(2 * tmp.re * tmp.im);
		z.re += c->re;
		z.im += c->im;
		*iter += 1;
	}
}

void		*bship_pthread(void *arg)
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
			bship_calc(&c, &iter, &(b->f->itera));
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
