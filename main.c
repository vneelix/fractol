/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 13:26:14 by vneelix           #+#    #+#             */
/*   Updated: 2020/01/08 14:56:31 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_exit(t_fractol *f, t_block *b)
{
	mlx_destroy_image(f->mlx.ptr, f->mlx.img_ptr);
	mlx_destroy_window(f->mlx.ptr, f->mlx.win);
	free(f->mlx.ptr);
	free(f);
	if (b != NULL)
		free(b);
	exit(0);
}

void		print_hud(t_fractol *f)
{
	mlx_string_put(f->mlx.ptr, f->mlx.win, 0,
		0, 0xFFFFFF, "moving : arrows");
	mlx_string_put(f->mlx.ptr, f->mlx.win, 0,
		15, 0xFFFFFF, "scale : mouse");
	mlx_string_put(f->mlx.ptr, f->mlx.win, 0,
		30, 0xFFFFFF, "c_change : pgup pgdown");
	mlx_string_put(f->mlx.ptr, f->mlx.win, 0,
		45, 0xFFFFFF, "iter_change : + -");
	mlx_string_put(f->mlx.ptr, f->mlx.win, 0,
		60, 0xFFFFFF, "frac_change : 1 - 7");
}

int			bernstein_color(int *iter, int *itera, double *shift)
{
	int		color;
	int		r;
	int		g;
	int		b;
	double	t;

	color = 0;
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
	while (i < W * H)
		((int*)(b->f->mlx.img_add))[i++] = 0;
	i = 0;
	while (i < T)
	{
		if ((ret = pthread_create(&((b + i)->tid), NULL,
			(b->f->fractol)[b->f->set], (b + i))) != 0)
			break ;
		i += 1;
	}
	while (i >= 0)
	{
		if (i == 0 && ret != 0)
			break ;
		pthread_join((b + (i--))->tid, NULL);
	}
	if (ret != 0)
		ft_exit(b->f, b);
	mlx_clear_window(b->f->mlx.ptr, b->f->mlx.win);
	mlx_put_image_to_window(b->f->mlx.ptr,
		b->f->mlx.win, b->f->mlx.img_ptr, 0, 0);
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
	mlx_hook(b->f->mlx.win, 2, 0, key_press, b);
	mlx_mouse_hook(b->f->mlx.win, mouse, b);
	if (b->f->set == 0)
		mlx_hook(b->f->mlx.win, 6, 0, mouse_mov, b);
	mlx_loop(b->f->mlx.ptr);
	return (0);
}
