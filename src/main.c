#include "fractol.h"

void		ft_exit(t_fractol *f, t_block *b)
{
	SDL_DestroyWindow(f->sdl.win);
	SDL_Quit();
	if (f != NULL)
		free(f);
	if (b != NULL)
		free(b);
	exit(0);
}

__uint32_t	bernstein_color(int *iter, int *itera, double *shift)
{
	__uint32_t	color;
	int			r;
	int			g;
	int			b;
	double		t;

	color = 0;
	if (*itera == 0)
		return (0);
	t = fabs(*shift - ((double)(*iter) / (double)(*itera)));
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	color |= r << 16;
	color |= g << 8;
	color |= b;
	return (color);
}

void		start_pthread(t_block *b)
{
	int		i;
	int		ret;

	i = 0;
	while (i < b->count)
	{
		if ((ret = pthread_create(&((b + i)->tid), NULL,
			(b->f->fractol)[b->f->set], (b + i))) != 0)
			break ;
		i += 1;
	}
	i = 0;
	while (i < b->count)
		pthread_join(b[i++].tid, NULL);
	if (ret != 0)
		ft_exit(b->f, b);
	SDL_UpdateWindowSurface(b->f->sdl.win);
}

int			main(int argc, char **argv)
{
	t_block			*b;

	if (argc != 2)
	{
		write(1, "usage: fractol [fract]\n", 23);
		write(1, "mandelbrot\n  julia\n multib0\n", 29);
		write(1, " multib3\n multib5\n multib6\n", 27);
		write(1, "  bship\n  bird\n", 15);
		return (-1);
	}
	if ((b = fractol_init(argv[1])) == NULL)
		return (0);
	start_pthread(b);
	sdl_loop(&(b->f->sdl), b);
	return (0);
}
