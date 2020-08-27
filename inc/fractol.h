#ifndef FRACTOL_H
# define FRACTOL_H

# define W 1024 // Size general window (W, H)
# define H 720
# define T 8 // Possible changes based on your central processor 

/*
** count iterations
*/
# define ITER 64

/*
** libc
*/
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_keyboard.h"
# include <pthread.h>

/*
** structs
*/
typedef void*(*t_func)(void *arg);

typedef struct	s_sdl{
	SDL_Window	*win;
	SDL_Surface	*surf;
	SDL_Event	event;
}				t_sdl;

typedef struct	s_complex{
	double		re;
	double		im;
}				t_complex;

typedef	struct	s_fractol
{
	int			set;
	t_sdl		sdl;
	double		scale;
	double		mov_x;
	double		mov_y;
	int			itera;
	t_complex	julia_c;
	int			julia_l;
	double		shift_c;
	t_func		fractol[16];
}				t_fractol;

typedef struct	s_block
{
	int			count;
	int			num;
	pthread_t	tid;
	int			y_0;
	int			y_m;
	t_fractol	*f;
}				t_block;

void			start_pthread(t_block *b);
void			*fractol_init(char *frac);
t_block			*blocks_create(t_fractol *f);
__uint32_t		bernstein_color(int *iter, int *itera, double *shift);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_exit(t_fractol *f, t_block *b);
void			scale(t_fractol *f, Sint32 state);

/*
** set
*/
void			*mandelbrot_pthread(void *arg);
void			*mandelbrot_init(void *arg);
void			*julia_pthread(void *arg);
void			*julia_init(void *arg);
void			*multib0_pthread(void *arg);
void			*multib0_init(void *arg);
void			*multib3_pthread(void *arg);
void			*multib3_init(void *arg);
void			*multib5_pthread(void *arg);
void			*multib5_init(void *arg);
void			*multib6_pthread(void *arg);
void			*multib6_init(void *arg);
void			*bship_pthread(void *arg);
void			*bship_init(void *arg);
void			*bird_pthread(void *arg);
void			*bird_init(void *arg);

/*
** sdl_func
*/
int				sdl_init(t_sdl *sdl);
int				sdl_loop(t_sdl *sdl, t_block *b);
int				sdl_mousehook(t_sdl *sdl, t_block *b);
int				sdl_keyhook(t_sdl *sdl, t_block *b);
int				sdl_mousemove(t_sdl *sdl, t_block *b);
int				sdl_winresize(t_sdl *sdl, t_block **b);

# define CONTROL_INFO	"Movement - arrows\nScale - mousewheel\nChange ITER - \'+\' \'-\'\n\
Color - pgup pgdown\nChange fract - 1, 2, 3, 4, 5, 6, 7, 0\nReset - return\n"

#endif
