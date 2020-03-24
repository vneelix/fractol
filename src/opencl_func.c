#include "fractol.h"

cl_int		opencl_release(t_opencl *cl, cl_int ret)
{
	if (cl->command_queue)
		ret = clReleaseCommandQueue(cl->command_queue);
	if (cl->context)
		ret = clReleaseContext(cl->context);
	if (cl->program)
		ret = clReleaseProgram(cl->program);
	if (cl->buff)
		ret = clReleaseMemObject(cl->buff);
	if (cl->kernel)
		ret = clReleaseKernel(cl->kernel);
	return (ret);
}

cl_int		opencl_kernel(t_fractol *f, char *file)
{
	int		ret;
	char	*cl_file;

	if ((ret = open(file, O_RDONLY)) < 0)
		return (-1);
	if ((cl_file = ft_getfile(ret)) == NULL)
		return (-1);
	f->cl.program = clCreateProgramWithSource(f->cl.context, 1, (const char **)(&cl_file), NULL, &ret);
	free(cl_file);
	if (ret)
		return (ret);
	if ((ret = clBuildProgram(f->cl.program, 1, &(f->cl.device_id), NULL, NULL, NULL)))
		return (ret);
	f->cl.kernel = clCreateKernel(f->cl.program, "main_func", &ret);
	if (ret)
		return (ret);
	return (ret);
}

cl_int		opencl_buff(t_fractol *f)
{
	cl_int	ret;
	size_t	mem_size;

	mem_size = f->sdl.surf->w * f->sdl.surf->h * f->sdl.surf->format->BytesPerPixel;
	f->cl.buff = clCreateBuffer(f->cl.context, CL_MEM_READ_WRITE, MEMOBJ_SIZE, NULL, &ret);
	if (ret)
		return (ret);
	if ((ret = clEnqueueWriteBuffer(f->cl.command_queue, f->cl.buff,
		CL_TRUE, 0, mem_size, f->sdl.surf->pixels, 0, NULL, NULL)))
		return (ret);
	return (ret);
}

cl_int		opencl_launch(t_fractol *f)
{
	cl_int	ret;
	size_t	global_work_size[1] = {f->sdl.surf->w * f->sdl.surf->h};
	size_t	mem_size = f->sdl.surf->w * f->sdl.surf->h * f->sdl.surf->format->BytesPerPixel;

	ret = clSetKernelArg(f->cl.kernel, 1, sizeof(int), &(f->sdl.surf->w));
	if (ret)
		return (ret);
	ret = clSetKernelArg(f->cl.kernel, 2, sizeof(int), &(f->set));
	if (ret)
		return (ret);
	ret = clSetKernelArg(f->cl.kernel, 3, sizeof(t_attr), &(f->attr));
	if (ret)
		return (ret);
	ret = clEnqueueNDRangeKernel(f->cl.command_queue, f->cl.kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
	if (ret)
		return (ret);
	ret = clEnqueueReadBuffer(f->cl.command_queue, f->cl.buff, CL_TRUE, 0, mem_size, f->sdl.surf->pixels, 0, NULL, NULL);
	return (ret);
}

cl_int		opencl_init(t_fractol *f)
{
	cl_int	ret;
	cl_uint	num;

	ret = clGetPlatformIDs(1, &(f->cl.platform_id), &num);
	if (ret)
		return (ret);
	ret = clGetDeviceIDs(f->cl.platform_id, CL_DEVICE_TYPE_GPU, 1, &(f->cl.device_id), &num);
	if (ret)
		return (ret);
	f->cl.context = clCreateContext(NULL, 1, &(f->cl.device_id), NULL, NULL, &ret);
	if (ret)
		return (ret);
	f->cl.command_queue = clCreateCommandQueue(f->cl.context, f->cl.device_id, 0, &ret);
	if (ret)
		return (ret);
	ret = opencl_kernel(f, "kernel.cl");
	if (ret)
		return (ret);
	ret = opencl_buff(f);
	if (ret)
		return (ret);
	ret = clSetKernelArg(f->cl.kernel, 0, sizeof(cl_mem), &(f->cl.buff));
	if (ret)
		return (ret);
	ret = opencl_launch(f);
	if (ret)
		return (ret);
	return (ret);
}