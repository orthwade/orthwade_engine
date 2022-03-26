#include "c_orientation.h"

namespace owd_lib
{
	c_orientation::c_orientation()
	{
		m_logger << "----orientation constructor START----\n";

		

		m_logger << "----orientation constructor OK----\n";
	}
	c_orientation::~c_orientation()
	{
		m_logger << "----orientation destructor START----\n";
		m_logger << "----orientation destructor OK----\n";
	}
	void c_orientation::rotate(float v, float h, float r)
	{
		//m_mtx.lock();
		{
			m_at_buffer = m_at;
			m_up_buffer = m_up;

			// OX' rotation:
			{
				m_u = m_up_buffer.cross(m_at_buffer);

				m_u_n = m_u.norm();

				m_u_x = m_u_n[0];
				m_u_y = m_u_n[1];
				m_u_z = m_u_n[2];

				m_rotate(v, m_u_z, m_u_y, m_u_z);
			}

			// OY' rotation:
			{
				m_u = m_up_buffer;

				m_u_n = m_u.norm();

				m_u_x = m_u_n[0];
				m_u_y = m_u_n[1];
				m_u_z = m_u_n[2];

				m_rotate(h, m_u_z, m_u_y, m_u_z);
			}

			// OZ' rotation:
			{
				m_u = m_at_buffer;

				m_u_n = m_u.norm();

				m_u_x = m_u_n[0];
				m_u_y = m_u_n[1];
				m_u_z = m_u_n[2];

				m_rotate(r, m_u_z, m_u_y, m_u_z);
			}
		}
		//m_mtx.unlock();
	}
	void c_orientation::rotate_(float v, float h, float r)
	{
		//m_mtx.lock();
		{
			// OX' rotation:
			{
				m_rotate(v, 1.0f, 0.0f, 0.0f);
			}

			// OY' rotation:
			{
				m_rotate(h, 0.0f, 1.0f, 0.0f);
			}

			// OZ' rotation:
			{
				m_rotate(r, 0.0f, 0.0f, 1.0f);
			}
		}
		//m_mtx.unlock();
		
	}
	void c_orientation::set_default()
	{
		//m_mtx.lock();
		{
			//m_angle_x = 0.0f;
			//m_angle_y = 0.0f;
			//m_angle_z = 0.0f;

			m_at.set(0.0, 0.0f, -1.0f);
			m_up.set(0.0, 1.0f, 0.0f);
			ori = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
			//m_at_buffer.set(0.0, 0.0f, -1.0f);
			//m_up_buffer.set(0.0, 1.0f, 0.0f);
		}
		//m_mtx.unlock();
	}
	xyz_t c_orientation::get_vec_at()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			result[0] = m_at.x;
			result[1] = m_at.y;
			result[2] = m_at.z;
		}
		//m_mtx.unlock();

		return result;
	}
	xyz_t c_orientation::get_vec_up()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			result[0] = m_up.x;
			result[1] = m_up.y;
			result[2] = m_up.z;
		}
		//m_mtx.unlock();

		return result;
	}
	void c_orientation::update_from_public_array()
	{
		m_at.set(ori[0], ori[1], ori[2]);
		m_up.set(ori[3], ori[4], ori[5]);
	}
	//void c_orientation::m_calculate_angle()
	//{
	//	//m_calculate_magnitude();
	//	m_calculate_normalized();
	//	//m_mtx.lock();
	//	{
	//		m_logger << "Calculating angle\n";
	//		// X rotation:
	//
	//		if (m_norm_y <= 0.0f && m_norm_z >= 0.0f) //alpha
	//		{
	//			m_angle_x = acosf(m_norm_z) * 180.0f / PI;
	//		}
	//		else if (m_norm_y <= 0.0f && m_norm_z <= 0.0f) // beta
	//		{
	//			m_angle_x = asinf(abs(m_norm_z)) * 180.0f / PI + 90.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_z <= 0.0f) // gamma
	//		{
	//			m_angle_x = asinf(m_norm_y) * 180.0f / PI + 180.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_z >= 0.0f) // phi
	//		{
	//			m_angle_x = 360.0f - acosf(m_norm_z) * 180.0f / PI;
	//		}
	//
	//		// Y rotation:
	//
	//		if (m_norm_z <= 0.0f && m_norm_x >= 0.0f) //alpha
	//		{
	//			m_angle_y = acosf(m_norm_x) * 180.0f / PI;
	//		}
	//		else if (m_norm_z <= 0.0f && m_norm_x <= 0.0f) // beta
	//		{
	//			m_angle_y = asinf(abs(m_norm_x)) * 180.0f / PI + 90.0f;
	//		}
	//		else if (m_norm_z >= 0.0f && m_norm_x <= 0.0f) // gamma
	//		{
	//			m_angle_y = asinf(m_norm_z) * 180.0f / PI + 180.0f;
	//		}
	//		else if (m_norm_z >= 0.0f && m_norm_x >= 0.0f) // phi
	//		{
	//			m_angle_y = 360.0f - acosf(m_norm_x) * 180.0f / PI;
	//		}
	//
	//		// Z rotation:
	//
	//		if (m_norm_y <= 0.0f && m_norm_x >= 0.0f) //alpha
	//		{
	//			m_angle_z = acosf(m_norm_x) * 180.0f / PI;
	//		}
	//		else if (m_norm_y <= 0.0f && m_norm_x <= 0.0f) // beta
	//		{
	//			m_angle_z = asinf(abs(m_norm_x)) * 180.0f / PI + 90.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_x <= 0.0f) // gamma
	//		{
	//			m_angle_z = asinf(m_norm_y) * 180.0f / PI + 180.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_x >= 0.0f) // phi
	//		{
	//			m_angle_z = 360.0f - acosf(m_norm_x) * 180.0f / PI;
	//		}
	//		m_logger << "Calculating angle OK. X rotation: " 
	//			<< m_angle_x << ";    Y rotation: " << m_angle_y << ";    Z rotation: " << m_angle_z;
	//	}
	//	//m_mtx.unlock();
	//}

}