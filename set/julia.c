/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 15:06:13 by vneelix           #+#    #+#             */
/*   Updated: 2020/01/07 14:16:18 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		*julia_init(void *arg)
{
	t_fractol *f;

	f = arg;
	f->scale = 200;
	f->mov_x = 2.425;
	f->mov_y = 1.75;
	f->julia_c.re = -0.4;
	f->julia_c.im = 0.6;
	f->julia_l = 0;
	f->itera = ITER;
	f->shift_c = 0;
	return (NULL);
}

static void	julia_calc(t_complex *z, t_complex *c, int *iter, int *itera)
{
	t_complex	tmp;

	*iter = 0;
	while (*iter < *itera && (z->re * z->re + z->im * z->im) <= 4)
	{
		tmp = *z;
		z->re = tmp.re * tmp.re - tmp.im * tmp.im;
		z->im = 2 * tmp.re * tmp.im;
		z->re += c->re;
		z->im += c->im;
		*iter += 1;
	}
}

void		*julia_pthread(void *arg)
{
	int			iter;
	t_block		*b;
	t_complex	z;

	b = arg;
	while (b->y < b->y1)
	{
		while (b->x < b->x1)
		{
			z.re = b->x / b->f->scale - b->f->mov_x;
			z.im = b->y / b->f->scale - b->f->mov_y;
			julia_calc(&z, &(b->f->julia_c), &iter, &(b->f->itera));
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
