#include "mandelbrot.h"
#include "color.h"
#include <cmath>
#include <algorithm>

namespace mandelbrot
{
	void render_t::init()
	{
	}

	void render_t::clear()
	{
	}

	int render(
		render_t          ri,
		render_callback_t callback,
		render_control_t  control)
	{
		// Prepare precision-related variables
		long double c_real, c_imag, step = ri.step;

		int iter_depth = 0;
		for (int i = 0; i != ri.height; ++i)
		{
			if (control && !control(i))
			{
				ri.y0 += step; // Increment imaginary part
				continue;
			}

			c_imag = ri.y0 + i * step;
			for (int j = 0; j != ri.width; ++j)
			{
				c_real = ri.x0 + j * step;

				// Iteration variables
				long double re = 0.0, im = 0.0, re2 = 0.0, im2 = 0.0;
				int iter = 1;
				for (; iter <= ri.max_iter; ++iter)
				{
					// z_{n+1} = z_n^2 + c
					im = 2.0 * re * im + c_imag;
					re = re2 - im2 + c_real;

					// Squares of real and imaginary parts
					re2 = re * re;
					im2 = im * im;

					// Check for escape condition
					if (re2 + im2 > 4.0)
						break;
				}

				int index = i * ri.width + j;
				if (ri.buffer) ri.buffer[index] = iter;
				if (iter <= ri.max_iter && iter > iter_depth)
					iter_depth = iter;

				// Calculate smooth iteration depth
				if (ri.smooth)
				{
					long double log_zn = 0.5 * log2(re2 + im2);
					ri.smooth[index] = iter + 1.0 - log2(log_zn);
				}
			}

			if (callback) callback(i);
		}

		return iter_depth;
	}
}
