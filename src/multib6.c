#include "fractol.h"

void		*multib6_init(void *arg)
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

static void	multib6_calc(t_complex *c, int *iter, int *itera)
{
	t_complex	z;
	t_complex	tmp;

	z.re = c->re;
	z.im = c->im;
	*iter = 0;
	while (*iter < *itera && (z.re * z.re + z.im * z.im) <= 4)
	{
		tmp = z;
		z.re = pow(tmp.re * tmp.re + tmp.im * tmp.im, 3)
			* cos(6 * atan2(tmp.im, tmp.re));
		z.im = pow(tmp.re * tmp.re + tmp.im * tmp.im, 3)
			* sin(6 * atan2(tmp.im, tmp.re));
		z.re += c->re;
		z.im += c->im;
		*iter += 1;
	}
}

void		*multib6_pthread(void *arg)
{
	int			iter;
	t_block		*b = arg;
	t_complex	c;
	int			x = 0, x_m, y = b->y_0;

	SDL_GetWindowSize(b->f->sdl.win, &x_m, NULL);
	while (y < b->y_m)
	{
		c.im = (double)(y) / b->f->scale - b->f->mov_y;
		while (x < x_m)
		{
			c.re = (double)(x) / b->f->scale - b->f->mov_x;
			multib6_calc(&c, &iter, &(b->f->itera));
			((__uint32_t*)(b->f->sdl.surf->pixels))[x + x_m * y] =
				bernstein_color(&iter, &(b->f->itera), &(b->f->shift_c));
			x += 1;
		}
		x = 0;
		y += 1;
	}
	pthread_exit(NULL);
}
