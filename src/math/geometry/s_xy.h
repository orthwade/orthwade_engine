#pragma once
#include <vector>

namespace owd_lib
{
	namespace geom
	{
		struct s_2d_coordinates_cartesian
		{
			s_2d_coordinates_cartesian();
			s_2d_coordinates_cartesian(float x, float y);

			s_2d_coordinates_cartesian  operator+ (const s_2d_coordinates_cartesian& other);
			s_2d_coordinates_cartesian& operator+=(const s_2d_coordinates_cartesian& other);
			s_2d_coordinates_cartesian  operator- (const s_2d_coordinates_cartesian& other);
			s_2d_coordinates_cartesian& operator-=(const s_2d_coordinates_cartesian& other);
			s_2d_coordinates_cartesian  operator* (float multilpier);
			s_2d_coordinates_cartesian& operator*=(float multilpier);
			s_2d_coordinates_cartesian  operator/ (float divisor);
			s_2d_coordinates_cartesian& operator/=(float divisor);

			float x{};
			float y{};
		};
	}
	
	typedef geom::s_2d_coordinates_cartesian xy_t;
}