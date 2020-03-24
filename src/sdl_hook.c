#include <fractol.h>

int		sdl_mousehook(t_sdl *sdl, t_fractol *f)
{
	if (sdl->event.wheel.y > 0)
		scale(f, sdl->event.wheel.y);
	else if (sdl->event.wheel.y < 0)
		scale(f, sdl->event.wheel.y);
	else
		return (1);
	return (0);
}

int		sdl_mousemove(t_sdl *sdl, t_fractol *f)
{
	int		x, y;

	SDL_GetMouseState(&x, &y);
	if (f->julia_l == 0)
	{
		(f->attr.julia_c)[0] = (x - sdl->surf->w / 2) / f->attr.scale;
		(f->attr.julia_c)[1] = (y - sdl->surf->h / 2) / f->attr.scale;
	}
	return (0);
}

void	sdl_message(t_sdl *sdl, SDL_Keycode key)
{
	if (key == SDLK_h)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Control", CONTROL_INFO, sdl->win);
}

int		sdl_keyhook(t_sdl *sdl, t_fractol *f)
{
	SDL_KeyCode key = sdl->event.key.keysym.sym;
	SDL_Keycode fractal_types = SDLK_1 | SDLK_2 | SDLK_3 | SDLK_4
								| SDLK_5 | SDLK_6 | SDLK_7 | SDLK_0;

	if (key == SDLK_ESCAPE)
		ft_exit(f);
	else if (key == SDLK_UP)
			f->attr.mov_y -= 5.0 / f->attr.scale;	
	else if (key == SDLK_DOWN)
			f->attr.mov_y += 5.0 / f->attr.scale;	
	else if (key == SDLK_LEFT)
			f->attr.mov_x -= 5.0 / f->attr.scale;	
	else if (key == SDLK_RIGHT)
			f->attr.mov_x += 5.0 / f->attr.scale;	
	else if (key == SDLK_MINUS)
			f->attr.itera -= (f->attr.itera <= 4 ? 0 : 4);	
	else if (key == SDLK_EQUALS)
			f->attr.itera += 4;	
	else if (key == SDLK_PAGEUP)
			f->attr.shift_c += (f->attr.shift_c < 1.0 ? 0.003 : 0);
	else if (key == SDLK_PAGEDOWN)
			f->attr.shift_c -= (f->attr.shift_c > 0.003 ? 0.003 : 0);
	else if (key == SDLK_SPACE && f->set == 0)
	{
		f->julia_l = (f->julia_l == 0 ? 1 : 0);
		if (f->julia_l == 0)
			julia_init(f);
	}
	else if (key == SDLK_RETURN && f->set != 0)
		(f->init)[f->set](f);
	else if ((key & fractal_types) == key)
	{
		f->set = key - SDLK_0;
		(f->init)[f->set](f);
	}
	else if (key == SDLK_h)
		sdl_message(sdl, key);
	else
		return (1);
	return (0);
}