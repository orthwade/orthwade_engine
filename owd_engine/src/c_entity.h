#pragma once
#include <list>
#include <memory>
#include <limits>
#include <mutex>

#include <owd_math.h>
#include <owd_lib.h>

namespace owd
{
	xy_t gravity();

	class c_entity
	{
	public:
		c_entity(float x, float y, float width, float height,
			float red, float green, float blue, float alpha, uint16_t level);

		c_entity(float x, float y, float radius,
			float red, float green, float blue, float alpha, uint16_t level);

		c_entity(float x, float y, float width, float height,
			std::wstring_view texture_name, uint16_t level);

		static std::shared_ptr<c_entity> make(float x, float y, float width, float height,
			float red, float green, float blue, float alpha, uint16_t level);

		~c_entity();


		bool point_is_inside(float x, float y);

		void resize(float multiplier);

		void set_position(float x, float y);
		void set_velocity(float x, float y);
		void set_acceleration(float x, float y);

		void move(float d_x, float d_y);
		void move_one_tick(float ticktime);

		inline float x() const { return m_x; }
		inline float y() const { return m_y; }

		inline float w() const { return m_w; }
		inline float h() const { return m_h; }

		inline xy_t const& velocity() const { return m_v; }
		inline xy_t const& acceleration() const { return m_a; }

		inline void set_to_delete() { m_deleted = true; }
		inline bool is_deleted() { return m_deleted; }

		float lifetime() const;
		bool lifetime_out();

		void start_async_lifetimer();

		inline void enable_interactive() { m_interactive = true; }
		inline void disable_interactive() { m_interactive = false; }
		inline bool interactive() { return m_interactive; }

	protected:
		bool m_interactive = false;
		float m_lifetime_ms = std::numeric_limits<float>::infinity();
		std::thread m_lifetime_thread{};
		std::atomic_bool m_lifetime_out = false;
		bool m_deleted = false;

		float m_x{};
		float m_y{};

		float m_w{};
		float m_h{};

		xy_t m_v{ 0.0f, 0.0f };
		xy_t m_a{ 0.0f, 0.0f };

		std::list<std::shared_ptr<c_graphic_unit>> m_units{};
	};
	typedef std::shared_ptr<c_entity> entity_t;

}