#pragma once
#include "c_openal_object.h"
#include "../math/vectors/c_orientation.h"

namespace owd_lib
{
	class c_listener : public c_openal_object
	{
	public:
		void set_position(float x, float y, float z);

		void set_gain(float gain);
		void set_velocity(float x, float y, float z);

		xyz_t position();

		xyz_t orientation_at();
		xyz_t orientation_up();
		ori_t orientation();

		/// <summary>
		/// Rotate orientation around OX', OY' or OZ' axes.
		/// OX', OY', OZ' do not necessarily match original axes OX, OY, OZ.
		/// OX' in general is the axis perpendicular both to AT and UP vectors(codirectional 
		/// with cross product of UP and AT vectors).
		/// OY' in general is the axis codirectional with UP vector.
		/// OZ' in general is the axis codirectional with AT vector.
		/// </summary>
		/// <param name="v">Angle in degrees to rotate orientation around OX' axis(vertical rotation).</param>
		/// <param name="h">Angle in degrees to rotate orientation around OY' axis(horizontal rotation)</param>
		/// <param name="r">Angle in degrees to rotate orientation around OZ' axis(roll)</param>
		void rotate(float v, float h, float r);

		/// <summary>
		/// Rotate vectors AT and UP around original axes OX, OY, OZ.
		/// </summary>
		/// <param name="v">Angle in degrees to rotate vectors AT and UP around OX axis</param>
		/// <param name="h">Angle in degrees to rotate vectors AT and UP around OY axis</param>
		/// <param name="r">Angle in degrees to rotate vectors AT and UP around OZ axis</param>
		void rotate_(float v, float h, float r);

		void set_default_orientation();

		float gain();

		static c_listener* get_instance();
		static void terminate();

	protected:
		float m_x{};
		float m_y{};
		float m_z{};

		c_orientation m_ori{};

		float m_gain{};

		float m_velocity_x{};
		float m_velocity_y{};
		float m_velocity_z{};

		static c_listener* m_singleton;

		c_listener();
		~c_listener();

		c_listener(const c_listener&) = delete;
		c_listener& operator=(const c_listener&) = delete;
	};
}