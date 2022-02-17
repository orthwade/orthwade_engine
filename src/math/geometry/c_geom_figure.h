#pragma once
#include <vector>
#include "../../misc/misc_defines.h"
#include "c_polar_coordinates.h"
#include "s_xy.h"

namespace owd
{
	

	class c_geom_figure
	{
	public:
		c_geom_figure();
		c_geom_figure(const std::vector<float>& vertices);
		~c_geom_figure();

		const std::vector<float>& vertices() const;

		virtual void set_vertices(const std::vector<float>& vertices);

		static xy_t centre(const std::vector<float>& vertices);

		virtual xy_t centre() const;

	protected:
		std::vector<float> m_vertices{}; // cartesian coordinate paires x, y.

		float m_x{};
		float m_y{};
	};
}