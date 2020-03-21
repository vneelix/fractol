#include "fractol.h"

void	scale(t_fractol *f, Sint32 state)
{
	int		x, y;

	SDL_GetMouseState(&x, &y);
	if (state > 0)
	{
		f->mov_x += x / (f->scale * 1.1) - x / f->scale;
		f->mov_y += y / (f->scale * 1.1) - y / f->scale;
		f->scale *= 1.1;
		f->itera += 2;
	}
	else if (state < 0)
	{
		f->mov_x += x / (f->scale / 1.1) - x / f->scale;
		f->mov_y += y / (f->scale / 1.1) - y / f->scale;
		f->scale /= 1.1;
		f->itera -= (f->itera > ITER ? 2 : 0);
	}
}
