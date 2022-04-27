#pragma once
#include <owd_graphics.h>

#include <list>
#include <memory>

namespace owd
{
	class c_entity
	{
	public:
		c_entity(float x, float y, float width, float height,
			float red, float green, float blue, float alpha, uint16_t level);

		~c_entity();

		void set_position(float x, float y);
		void move(float d_x, float d_y);

		inline float x() const { return m_x; }
		inline float y() const { return m_y; }

	protected:
		float m_x{};
		float m_y{};

		std::list<std::shared_ptr<c_graphic_unit>> m_units{};
	};
	typedef std::shared_ptr<c_entity> entity_t;

}