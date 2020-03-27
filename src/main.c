#include "fractol.h"

void		ft_exit(t_fractol *f)
{
	SDL_DestroyWindow(f->sdl->win);
	SDL_Quit();
	opencl_release(&(f->cl), 0);
	if (f != NULL)
		free(f);
	exit(0);
}

int			main(int argc, char **argv)
{
	t_fractol *f;

	if (argc != 2)
	{
		write(1, "usage: fractol [fract]\n", 23);
		write(1, "mandelbrot\n  julia\n multib0\n", 29);
		write(1, " multib3\n multib5\n multib6\n", 27);
		write(1, "  bship\n  bird\n", 15);
		return (-1);
	}
	if ((f = fractol_init(argv[1])) == NULL)
		return (0);
	if (opencl_init(f))
	{
		write(1, "OpenCL initialize failure\n", 26);
		ft_exit(f);
	}
	SDL_UpdateWindowSurface(f->sdl.win);
	sdl_loop(&(f->sdl), f);
	return (0);
}
