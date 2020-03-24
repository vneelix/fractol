#include "fractol.h"

int		julia_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 200;
	f->attr.mov_x = 2.425;
	f->attr.mov_y = 1.75;
	f->attr.julia_c[0] = -0.4;
	f->attr.julia_c[1] = 0.6;
	f->julia_l = 0;
	f->attr.itera = ITER;
	f->attr.shift_c = 0;
	return (0);
}

int		mandelbrot_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 300;
	f->attr.mov_x = 2.2;
	f->attr.mov_y = 1.2;
	f->attr.itera = ITER;
	f->attr.shift_c = 0;
	return (0);
}

int		multib0_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 200;
	f->attr.mov_x = 2.5;
	f->attr.mov_y = 1.8;
	f->attr.itera = ITER;
	f->attr.shift_c = 0.08;
	return (0);
}

int		multib3_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 250;
	f->attr.mov_x = 2.04;
	f->attr.mov_y = 1.4;
	f->attr.itera = ITER;
	f->attr.shift_c = 0;
	return (0);
}

int		multib5_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 250;
	f->attr.mov_x = 2.04;
	f->attr.mov_y = 1.4;
	f->attr.itera = ITER;
	f->attr.shift_c = 0;
	return (0);
}

int		multib6_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 250;
	f->attr.mov_x = 2.04;
	f->attr.mov_y = 1.4;
	f->attr.itera = ITER;
	f->attr.shift_c = 0;
	return (0);
}

int		bship_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 250;
	f->attr.mov_x = 2.5;
	f->attr.mov_y = 2.0;
	f->attr.itera = ITER;
	f->attr.shift_c = 1.0;
	return (0);
}

int		bird_init(void *arg)
{
	t_fractol *f = arg;
	
	f->attr.scale = 250;
	f->attr.mov_x = 2.75;
	f->attr.mov_y = 1.5;
	f->attr.itera = ITER;
	f->attr.shift_c = 1.0;
	return (0);
}
