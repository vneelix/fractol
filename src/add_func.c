#include "fractol.h"

void	scale(t_fractol *f, Sint32 state)
{
	int		x, y;

	SDL_GetMouseState(&x, &y);
	if (state > 0)
	{
		f->attr.mov_x += x / (f->attr.scale * 1.1) - x / f->attr.scale;
		f->attr.mov_y += y / (f->attr.scale * 1.1) - y / f->attr.scale;
		f->attr.scale *= 1.1;
		f->attr.itera += 2;
	}
	else if (state < 0)
	{
		f->attr.mov_x += x / (f->attr.scale / 1.1) - x / f->attr.scale;
		f->attr.mov_y += y / (f->attr.scale / 1.1) - y / f->attr.scale;
		f->attr.scale /= 1.1;
		f->attr.itera -= (f->attr.itera > ITER ? 2 : 0);
	}
}
