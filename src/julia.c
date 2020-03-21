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
	t_block		*b = arg;
	t_complex	z;
	int			x = 0, x_m, y = b->y_0;

	SDL_GetWindowSize(b->f->sdl.win, &x_m, NULL);
	while (y < b->y_m)
	{
		while (x < x_m)
		{
			z.re = (double)(x) / b->f->scale - b->f->mov_x;
			z.im = (double)(y) / b->f->scale - b->f->mov_y;
			julia_calc(&z, &(b->f->julia_c), &iter, &(b->f->itera));
			((__uint32_t*)(b->f->sdl.surf->pixels))[x + x_m * y] =
				bernstein_color(&iter, &(b->f->itera), &(b->f->shift_c));
			x += 1;
		}
		x = 0;
		y += 1;
	}
	pthread_exit(NULL);
}
