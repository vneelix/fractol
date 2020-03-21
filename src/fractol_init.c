#include "fractol.h"

static int		frac_type(char *frac)
{
	if (ft_strcmp(frac, "julia") == 0)
		return (0);
	else if (ft_strcmp(frac, "mandelbrot") == 0)
		return (1);
	else if (ft_strcmp(frac, "multib0") == 0)
		return (2);
	else if (ft_strcmp(frac, "multib3") == 0)
		return (3);
	else if (ft_strcmp(frac, "multib5") == 0)
		return (4);
	else if (ft_strcmp(frac, "multib6") == 0)
		return (5);
	else if (ft_strcmp(frac, "bship") == 0)
		return (6);
	else if (ft_strcmp(frac, "bird") == 0)
		return (7);
	else
	{
		write(1, "usage: fractol [fract]\n", 23);
		write(1, "mandelbrot\n  julia\n multib0\n", 29);
		write(1, " multib3\n multib5\n multib6\n", 27);
		write(1, "  bship\n  bird\n", 15);
		return (-1);
	}
}

static void		fill_func(t_fractol *f)
{
	(f->fractol)[0] = julia_pthread;
	(f->fractol)[1] = mandelbrot_pthread;
	(f->fractol)[2] = multib0_pthread;
	(f->fractol)[3] = multib3_pthread;
	(f->fractol)[4] = multib5_pthread;
	(f->fractol)[5] = multib6_pthread;
	(f->fractol)[6] = bship_pthread;
	(f->fractol)[7] = bird_pthread;
	(f->fractol)[8] = julia_init;
	(f->fractol)[9] = mandelbrot_init;
	(f->fractol)[10] = multib0_init;
	(f->fractol)[11] = multib3_init;
	(f->fractol)[12] = multib5_init;
	(f->fractol)[13] = multib6_init;
	(f->fractol)[14] = bship_init;
	(f->fractol)[15] = bird_init;
}

static void		blocks_init(t_block *b, t_fractol *f, int *h, int count)
{
	int		i = 0, offset = 0, mod = 0;

	mod = *h % count;
	offset = *h / count;
	((f->fractol)[f->set + 8])(f);
	while (i < count)
	{
		(b + i)->count = count;
		(b + i)->num = i;
		(b + i)->f = f;
		if (i == (count - 1) && mod != 0)
		{
			(b + i)->y_0 = (b + i - 1)->y_m;
			(b + i)->y_m = *h;
		}
		else
		{
			(b + i)->y_0 = i * offset;
			(b + i)->y_m = (b + i)->y_0 + offset;
		}
		i += 1;
	}
}

t_block			*blocks_create(t_fractol *f)
{
	t_block		*b;
	int			h = 0, c = 0;

	SDL_GetWindowSize(f->sdl.win, NULL, &h);
	if ((c = T + (h % T == 0 ? 0 : 1)) == 0)
		ft_exit(f, NULL);
	if ((b = (t_block*)malloc(sizeof(t_block) * c)) == NULL)
		ft_exit(f, NULL);
	blocks_init(b, f, &h, c);
	return (b);
}

void			*fractol_init(char *frac)
{
	t_fractol	*f;

	if ((f = (t_fractol*)malloc(sizeof(t_fractol))) == NULL)
		return (NULL);
	if ((f->set = frac_type(frac)) == (-1))
	{
		free(f);
		return (NULL);
	}
	if (sdl_init(&(f->sdl)) == (-1))
	{
		free(f);
		return (NULL);
	}
	fill_func(f);
	return (blocks_create(f));
}
