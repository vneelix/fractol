#ifndef FRACTOL_H
# define FRACTOL_H

# define W 1024 // Size general window (W, H)
# define H 768
# define BUFF_SIZE 4096 // file_read
# define MEMOBJ_SIZE 100663296 // size MEMOBJ OpenCL bytes (current 96 MiB)

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
# include <SDL2/SDL.h>
# include <SDL2/SDL_keyboard.h>
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
# include <OpenCL/opencl.h>
#else
# include <CL/cl.h>
#endif

/*
** structs
*/
typedef int(*t_func)(void *arg);

typedef struct	s_sdl{
	SDL_Window			*win;
	SDL_Surface			*surf;
	SDL_Event			event;
}				t_sdl;

typedef struct __attribute__ ((aligned)) s_attr{
	double				scale;
	double				mov_x;
	double				mov_y;
	int					itera;
	double				julia_c[2];
	double				shift_c;
}				t_attr;

typedef struct	s_opencl{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_mem				buff;
	cl_kernel			kernel;
}				t_opencl;

typedef	struct	s_fractol
{
	int					set;
	t_sdl				sdl;
	t_opencl			cl;
	t_attr				attr;
	int					julia_l;
	t_func				init[8];
}				t_fractol;

t_fractol				*fractol_init(char *frac);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_exit(t_fractol *f);
void					scale(t_fractol *f, Sint32 state);
char					*ft_getfile(int fd);
int						julia_init(void *arg);
int						mandelbrot_init(void *arg);
int						multib0_init(void *arg);
int						multib3_init(void *arg);
int						multib5_init(void *arg);
int						multib6_init(void *arg);
int						bship_init(void *arg);
int						bird_init(void *arg);

/*
** sdl_func
*/
int						sdl_init(t_sdl *sdl);
int						sdl_loop(t_sdl *sdl, t_fractol *f);
int						sdl_mousehook(t_sdl *sdl, t_fractol *f);
int						sdl_keyhook(t_sdl *sdl, t_fractol *f);
int						sdl_mousemove(t_sdl *sdl, t_fractol *f);

/*
** opencl_func
*/
cl_int					opencl_init(t_fractol *f);
cl_int					opencl_launch(t_fractol *f);
cl_int					opencl_buff(t_fractol *f);
cl_int					opencl_kernel(t_fractol *f, char *file);
cl_int					opencl_release(t_opencl *cl, cl_int ret);

# define CONTROL_INFO	"Movement - arrows\nScale - mousewheel\nChange ITER - \'+\' \'-\'\n\
Color- pgup pgdown\nChange fract - 1, 2, 3, 4, 5, 6, 7, 0\nReset - return\n"
#endif
