/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 13:26:20 by vneelix           #+#    #+#             */
/*   Updated: 2020/01/08 14:45:58 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		mlx_prepare(t_fractol *f, int line, int color, int endian)
{
	if ((f->mlx.ptr = mlx_init()) == NULL)
		return (-1);
	if ((f->mlx.win = mlx_new_window(f->mlx.ptr, W, H, "fractol")) == NULL)
	{
		free(f->mlx.ptr);
		return (-1);
	}
	if ((f->mlx.img_ptr = mlx_new_image(f->mlx.ptr, W, H)) == NULL)
	{
		mlx_destroy_window(f->mlx.ptr, f->mlx.win);
		free(f->mlx.ptr);
		return (-1);
	}
	if ((f->mlx.img_add = mlx_get_data_addr(
		f->mlx.img_ptr, &color, &line, &endian)) == NULL)
	{
		mlx_destroy_image(f->mlx.ptr, f->mlx.win);
		mlx_destroy_window(f->mlx.ptr, f->mlx.win);
		free(f->mlx.ptr);
		return (-1);
	}
	return (0);
}

static void		blocks_init(t_block *b, t_fractol *f)
{
	int		i;

	i = 0;
	((f->fractol)[f->set + 8])(f);
	while (i < T)
	{
		(b + i)->num = i;
		(b + i)->f = f;
		(b + i)->x = (b + i)->num % 8 * 128;
		(b + i)->y = (b + i)->num / 8 * 90;
		(b + i)->x1 = (b + i)->x + 128;
		(b + i)->y1 = (b + i)->y + 90;
		i += 1;
	}
}

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

void			*fractol_init(char *frac)
{
	t_fractol	*f;
	t_block		*b;

	if ((f = (t_fractol*)malloc(sizeof(t_fractol))) == NULL)
		return (NULL);
	if ((f->set = frac_type(frac)) == (-1))
	{
		free(f);
		return (NULL);
	}
	if (mlx_prepare(f, W, H, 0) == (-1))
	{
		free(f);
		return (NULL);
	}
	if ((b = (t_block*)malloc(sizeof(t_block) * T)) == NULL)
		ft_exit(f, NULL);
	fill_func(f);
	blocks_init(b, f);
	return (b);
}
