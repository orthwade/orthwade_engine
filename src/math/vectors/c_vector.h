#pragma once
#include "../../debug/logger/logger.h"
#include "../../misc/misc_defines.h"

namespace owd_lib
{
	/// <summary>
	/// Object of a 3D-space vector with elements x, y, z.
	/// </summary>
	class c_3d_vector
	{
	public:
		c_3d_vector();
		c_3d_vector(float x, float y, float z);
		~c_3d_vector();

		c_3d_vector& operator=(const c_3d_vector& other);
		c_3d_vector(const c_3d_vector& other);

		void set(float x, float y, float z); // set vector elements
		xyz_t get(); // get vector elements
		float mangitude(); // get magnitude of the vector
		xyz_t norm(); // get normalized vector elements

		float x{};
		float y{};
		float z{};

		/// <summary>
		/// Rotate vector around arbitrary axis u = (u_x, u_y, u_z).
		/// </summary>
		/// <param name="vec">Vector to rotate</param>
		/// <param name="angle">Angle in degrees to rotate vector</param>
		/// <param name="u_x">X component of a unit vector describing rotation axis</param>
		/// <param name="u_y">Y component of a unit vector describing rotation axis</param>
		/// <param name="u_z">Z component of a unit vector describing rotation axis</param>
		static void rotate_vector(c_3d_vector& vec, float angle, float u_x, float u_y, float u_z);

		c_3d_vector cross(const c_3d_vector& other);

	private:
		std::mutex m_mtx{};
	};
}


