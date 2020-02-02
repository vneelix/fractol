/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:22:58 by vneelix           #+#    #+#             */
/*   Updated: 2020/01/08 14:58:29 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	scale(t_fractol *f, int k, int x, int y)
{
	if (k == 4)
	{
		f->mov_x += x / (f->scale * 1.1) - x / f->scale;
		f->mov_y += y / (f->scale * 1.1) - y / f->scale;
		f->scale *= 1.1;
		f->itera += 2;
	}
	else if (k == 5)
	{
		f->mov_x += x / (f->scale / 1.1) - x / f->scale;
		f->mov_y += y / (f->scale / 1.1) - y / f->scale;
		f->scale /= 1.1;
		f->itera -= (f->itera > ITER ? 2 : 0);
	}
}

void		key_part2(int *keycode, t_fractol *f, void *arg)
{
	if (*keycode == 49 && f->set == 0)
	{
		f->julia_l = (f->julia_l == 0 ? 1 : 0);
		if (f->julia_l == 0)
		{
			julia_init(f);
			start_pthread(arg);
		}
	}
	else if (*keycode >= 83 && *keycode <= 89
		&& f->set != 0 && (*keycode - 83 + 1) != f->set)
	{
		f->set = *keycode - 83 + 1;
		((f->fractol)[f->set + 8])(f);
		start_pthread(arg);
	}
	else if (*keycode == 78)
		f->itera -= (f->itera <= 4 ? 0 : 4);
	else if (*keycode == 69)
		f->itera += 4;
	else if (*keycode == 116)
		f->shift_c += 0.005;
	else if (*keycode == 121)
		f->shift_c -= (f->shift_c > 0.005 ? 0.005 : 0);
}

int			key_press(int keycode, void *arg)
{
	t_fractol	*f;

	f = ((t_block*)arg)->f;
	if (keycode == 53)
		ft_exit(f, arg);
	else if (keycode == 36 && f->set != 0)
		((f->fractol)[f->set + 8])(f);
	else if (keycode == 126)
		f->mov_y -= (5 / f->scale);
	else if (keycode == 125)
		f->mov_y += (5 / f->scale);
	else if (keycode == 123)
		f->mov_x -= (5 / f->scale);
	else if (keycode == 124)
		f->mov_x += (5 / f->scale);
	else
		key_part2(&keycode, f, arg);
	if (keycode == 36 || keycode == 126 || keycode == 125
		|| keycode == 123 || keycode == 124 || keycode == 78
			|| keycode == 69 || keycode == 116 || keycode == 121)
		start_pthread(arg);
	if (keycode == 82)
		print_hud(f);
	return (0);
}

int			mouse(int keycode, int x, int y, void *arg)
{
	if ((keycode == 4 || keycode == 5)
		&& (((t_block*)(arg))->f->julia_l == 1
			|| ((t_block*)(arg))->f->set != 0))
	{
		scale(((t_block*)(arg))->f, keycode, x, y);
		start_pthread(arg);
	}
	return (0);
}

int			mouse_mov(int x, int y, void *arg)
{
	if (x >= 0 && x < W && y >= 0 && y < H
		&& ((t_block*)(arg))->f->julia_l == 0)
	{
		((t_block*)(arg))->f->julia_c.re =
			(x - 512) / ((t_block*)(arg))->f->scale;
		((t_block*)(arg))->f->julia_c.im =
			(y - 360) / ((t_block*)(arg))->f->scale;
		start_pthread(arg);
	}
	return (0);
}
