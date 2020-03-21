#include <fractol.h>

int		sdl_winresize(t_sdl *sdl, t_block **b)
{
	int			w, h;
	t_fractol	*f;

	SDL_GetWindowSize(sdl->win, &w, &h);
	sdl->surf = SDL_GetWindowSurface(sdl->win);
	f = (*b)->f;
	free(*b);
	*b = blocks_create(f);
	return (0);
}

int		sdl_mousehook(t_sdl *sdl, t_block *b)
{
	if (sdl->event.wheel.y > 0)
		scale(b->f, sdl->event.wheel.y);
	else if (sdl->event.wheel.y < 0)
		scale(b->f, sdl->event.wheel.y);
	else
		return (1);
	return (0);
}

int		sdl_mousemove(t_sdl *sdl, t_block *b)
{
	int		x, y;

	SDL_GetMouseState(&x, &y);
	if (b->f->julia_l == 0)
	{
		b->f->julia_c.re = (x - sdl->surf->w / 2) / b->f->scale;
		b->f->julia_c.im = (y - sdl->surf->h / 2) / b->f->scale;
	}
	return (0);
}

void	sdl_message(t_sdl *sdl, SDL_Keycode key)
{
	if (key == SDLK_h)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Control", CONTROL_INFO, sdl->win);
}

int		sdl_keyhook(t_sdl *sdl, t_block *b)
{
	SDL_KeyCode key = sdl->event.key.keysym.sym;
	SDL_Keycode fractal_types = SDLK_1 | SDLK_2 | SDLK_3 | SDLK_4
								| SDLK_5 | SDLK_6 | SDLK_7 | SDLK_0;

	if (key == SDLK_ESCAPE)
		ft_exit(b->f, b);
	else if (key == SDLK_UP)
			b->f->mov_y -= 5.0 / b->f->scale;	
	else if (key == SDLK_DOWN)
			b->f->mov_y += 5.0 / b->f->scale;	
	else if (key == SDLK_LEFT)
			b->f->mov_x -= 5.0 / b->f->scale;	
	else if (key == SDLK_RIGHT)
			b->f->mov_x += 5.0 / b->f->scale;	
	else if (key == SDLK_MINUS)
			b->f->itera -= (b->f->itera <= 4 ? 0 : 4);	
	else if (key == SDLK_EQUALS)
			b->f->itera += 4;	
	else if (key == SDLK_PAGEUP)
			b->f->shift_c += (b->f->shift_c < 1.0 ? 0.003 : 0);
	else if (key == SDLK_PAGEDOWN)
			b->f->shift_c -= (b->f->shift_c > 0.003 ? 0.003 : 0);
	else if (key == SDLK_SPACE && b->f->set == 0)
	{
		b->f->julia_l = (b->f->julia_l == 0 ? 1 : 0);
		if (b->f->julia_l == 0)
			julia_init(b->f);
	}
	else if (key == SDLK_RETURN && b->f->set != 0)
		((b->f->fractol)[b->f->set + 8])(b->f);
	else if ((key & fractal_types) == key)
	{
		b->f->set = key - SDLK_0;
		((b->f->fractol)[b->f->set + 8])(b->f);
	}
	else if (key == SDLK_h)
		sdl_message(sdl, key);
	else
		return (1);
	return (0);
}