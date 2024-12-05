#ifndef __MANDELBROT_H
#define __MANDELBROT_H

#include <cstdint>
#include <functional>
#include "color.h"

namespace mandelbrot
{
	typedef std::function<void(int)> render_callback_t;
	typedef std::function<bool(int)> render_control_t;

	struct render_t
	{
		int width, height;
		// linearized height * width matrix
		// its value is the iteration depth
		int *buffer;
		// linearized height * width matrix
		// its value is the (smooth) iteration depth
		double *smooth;
		// maximum iteration depth
		int max_iter;
		// precision of floating-point variables
		double prec;
		// coordinate of left-top point
		long double x0, y0;
		// distance between two adjacent points
		long double step;

		void init();
		void clear();
	};

	int render(
		render_t render_info, 
		render_callback_t = nullptr, 
		render_control_t  = nullptr);
}

#endif // __MANDELBROT_H
