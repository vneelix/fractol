#include "fractol.h"

int			sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (-1);
	if ((sdl->win = SDL_CreateWindow("Fractol",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					W, H, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN)) == NULL)
	{
		SDL_Quit();
		return (-1);
	}
	if ((sdl->surf = SDL_GetWindowSurface(sdl->win)) == NULL)
	{
		SDL_DestroyWindow(sdl->win);
		SDL_Quit();
		return (-1);
	}
	return (0);
}

static void	correct_queue(void)
{
	SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	SDL_EventState(SDL_MOUSEWHEEL, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
}

int			sdl_loop(t_sdl *sdl, t_block *b)
{
	int			ret = 1, quit = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&(sdl->event)))
		{
			if (sdl->event.type == SDL_QUIT)
				quit = 1;
			else if (sdl->event.type == SDL_KEYDOWN)
				ret = sdl_keyhook(sdl, b);
			else if (sdl->event.type == SDL_MOUSEMOTION)
			{
				if (b->f->set == 0 && b->f->julia_l == 0)
					ret = sdl_mousemove(sdl, b);
			}
			else if (sdl->event.type == SDL_MOUSEWHEEL)
			{
				if ((b->f->set == 0 && b->f->julia_l == 1) || b->f->set != 0)
					ret = sdl_mousehook(sdl, b);
			}
			else if (sdl->event.window.event == SDL_WINDOWEVENT_RESIZED)
				ret = sdl_winresize(sdl, &(b));
			else if (sdl->event.window.event == SDL_WINDOWEVENT_RESTORED)
				SDL_UpdateWindowSurface(sdl->win);
			else
				continue ;
			if (!ret)
			{
				correct_queue();
				start_pthread(b);
			}
			ret = 1;
		}
	}
	ft_exit(b->f, b);
	return (0);
}
