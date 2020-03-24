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

t_fractol	*fractol_init(char *frac)
{
	t_fractol	*f;

	if ((f = (t_fractol*)malloc(sizeof(t_fractol))) == NULL)
		return (NULL);
	if ((f->set = frac_type(frac)) == (-1))
	{
		free(f);
		return (NULL);
	}
	(f->init)[0] = julia_init;
	(f->init)[1] = mandelbrot_init;
	(f->init)[2] = multib0_init;
	(f->init)[3] = multib3_init;
	(f->init)[4] = multib5_init;
	(f->init)[5] = multib6_init;
	(f->init)[6] = bship_init;
	(f->init)[7] = bird_init;
	if (sdl_init(&(f->sdl)) == (-1))
	{
		free(f);
		return (NULL);
	}
	(f->init)[f->set](f);
	return (f);
}
