#pragma OPENCL EXTENSION cl_khr_fp64 : enable

struct __attribute__ ((aligned)) s_attr{
	double		scale;
	double		mov_x;
	double		mov_y;
	int			itera;
	double		julia_c[2];
	double		shift_c;
};

__kernel void	julia(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;

	y = pixel / w;
	x = pixel - y * w;
	z = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	c = (double2)(attr.julia_c[0], attr.julia_c[1]);
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		z.x = tmp.x * tmp.x - tmp.y * tmp.y;
		z.y = 2 * tmp.x * tmp.y;
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	mandelbrot(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;

	y = pixel / w;
	x = pixel - y * w;
	c = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	z = c;
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		z.x = tmp.x * tmp.x - tmp.y * tmp.y;
		z.y = 2 * tmp.x * tmp.y;
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	multib0(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;
	double	d;

	y = pixel / w;
	x = pixel - y * w;
	c = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	z = c;
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		d = tmp.x * tmp.x * tmp.x * tmp.x
			+ 2 * tmp.x * tmp.x * tmp.y * tmp.y
				+ tmp.y * tmp.y * tmp.y * tmp.y;
		if (d == (double)(0))
			break ;
		z.x = (tmp.x * tmp.x - tmp.y * tmp.y) / d;
		z.y = -2 * tmp.x * tmp.y / d;
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	multib3(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;

	y = pixel / w;
	x = pixel - y * w;
	c = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	z = c;
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		z.x = tmp.x * tmp.x * tmp.x - 3 * tmp.x * tmp.y * tmp.y;
		z.y = 3 * tmp.x * tmp.x * tmp.y - tmp.y * tmp.y * tmp.y;
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	multib5(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;

	y = pixel / w;
	x = pixel - y * w;
	c = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	z = c;
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		z.x = tmp.x * tmp.x * tmp.x * tmp.x * tmp.x
			- 10 * tmp.x * tmp.x * tmp.x * tmp.y * tmp.y
				+ 5 * tmp.x * tmp.y * tmp.y * tmp.y * tmp.y;
		z.y = 5 * tmp.x * tmp.x * tmp.x * tmp.x * tmp.y
			- 10 * tmp.x * tmp.x * tmp.y * tmp.y * tmp.y
				+ tmp.y * tmp.y * tmp.y * tmp.y * tmp.y;
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	multib6(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;

	y = pixel / w;
	x = pixel - y * w;
	c = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	z = c;
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		z.x = pow(tmp.x * tmp.x + tmp.y * tmp.y, 3)
			* cos(6 * atan2(tmp.y, tmp.x));
		z.y = pow(tmp.x * tmp.x + tmp.y * tmp.y, 3)
			* sin(6 * atan2(tmp.y, tmp.x));
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	bship(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;

	y = pixel / w;
	x = pixel - y * w;
	c = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	z = c;
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		z.x = tmp.x * tmp.x - tmp.y * tmp.y;
		z.y = fabs(2 * tmp.x * tmp.y);
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	bird(__global unsigned int *pixels, int w, struct s_attr attr)
{
	int		x, y, iter;
	int		pixel = get_global_id(0);
	double2	z, c, tmp;

	y = pixel / w;
	x = pixel - y * w;
	c = (double2)((double)(x) / attr.scale - attr.mov_x, (double)(y) / attr.scale - attr.mov_y);
	z = c;
	iter = 0;
	while (iter < attr.itera && (z.x * z.x + z.y * z.y) <= 4)
	{
		tmp = z;
		z.x = fabs(tmp.x * tmp.x - tmp.y * tmp.y);
		z.y = 2 * tmp.x * tmp.y;
		z.x += c.x;
		z.y += c.y;
		iter += 1;
	}
	double			t = fabs(attr.shift_c - (double)(iter) / (double)(attr.itera));
	unsigned int	r = (unsigned int)(9 * (1 - t) * t * t * t * 255);
	unsigned int	g = (unsigned int)(15 * (1 - t) * (1 - t) * t * t * 255);
	unsigned int	b = (unsigned int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	unsigned int	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	pixels[pixel] = color;
}

__kernel void	main_func(__global unsigned int *pixels, int w, int set, struct s_attr attr)
{
	if (set == 0)
		julia(pixels, w, attr);
	if (set == 1)
		mandelbrot(pixels, w, attr);
	if (set == 2)
		multib0(pixels, w, attr);
	if (set == 3)
		multib3(pixels, w, attr);
	if (set == 4)
		multib5(pixels, w, attr);
	if (set == 5)
		multib6(pixels, w, attr);
	if (set == 6)
		bship(pixels, w, attr);
	if (set == 7)
		bird(pixels, w, attr);
}
