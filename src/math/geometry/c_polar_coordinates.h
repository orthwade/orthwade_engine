#pragma once

namespace owd
{
	struct s_polar_coordinates
	{
		s_polar_coordinates();
		s_polar_coordinates(float r_, float a_);
		float r{}; // radial coordinate
		float a{}; // angle in degrees
	};
	
	typedef s_polar_coordinates pc_t;
}