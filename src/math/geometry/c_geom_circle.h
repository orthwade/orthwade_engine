#pragma once
#include "c_geom_figure.h"

namespace owd_lib
{
	class c_geom_circle : public c_geom_figure
	{
	public:
		c_geom_circle();
		c_geom_circle(float x, float y, float r);
		~c_geom_circle();

		float radius() const;

		void set(float centre_x, float centre_y, float radius);

	protected:
		uint16_t m_triangles_count = 90;

		float m_x{};
		float m_y{};
		float m_r{};
	};
}