#pragma once
#include "s_xy.h"

namespace owd
{
	typedef std::vector<float> vertices_t;
	namespace geom
	{
		struct s_rect
		{
			s_rect()
				:
				m_x(),
				m_y(),
				m_w(),
				m_h()
			{

			}
			s_rect(float centre_x, float centre_y, float width, float height)
				:
				m_x(centre_x),
				m_y(centre_y),
				m_w(width),
				m_h(height)
			{

			}
			inline float bottom_left_x()
			{
				return m_x - m_w / 2.0f;
			}
			inline float bottom_left_y()
			{
				return m_y - m_h / 2.0f;
			}
			inline float bottom_right_x()
			{
				return m_x + m_w / 2.0f;
			}
			inline float bottom_right_y()
			{
				return m_y - m_h / 2.0f;
			}
			inline float top_left_x()
			{
				return m_x - m_w / 2.0f;
			}
			inline float top_left_y()
			{
				return m_y + m_h / 2.0f;
			}
			inline float top_right_x()
			{
				return m_x + m_w / 2.0f;
			}
			inline float top_right_y()
			{
				return m_y + m_h / 2.0f;
			}
			////
			inline s_2d_coordinates_cartesian bottom_left()
			{
				return { bottom_left_x(), bottom_left_y() };
			}
			inline s_2d_coordinates_cartesian bottom_right()
			{
				return { bottom_right_x(), bottom_right_y() };
			}
			inline s_2d_coordinates_cartesian top_left()
			{
				return { top_left_x(), top_left_y() };
			}
			inline s_2d_coordinates_cartesian top_right()
			{
				return { top_right_x(), top_right_y() };
			}

			virtual vertices_t vertices();

			float m_x{};
			float m_y{};
			float m_w{};
			float m_h{};
		};
	}
}