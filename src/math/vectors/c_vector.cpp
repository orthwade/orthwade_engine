#include "c_vector.h"
namespace owd_lib
{
	c_3d_vector::c_3d_vector()
	{
	}
	c_3d_vector::c_3d_vector(float x, float y, float z)
	{
		set(x, y, z);
	}
	c_3d_vector::~c_3d_vector()
	{
	}
	c_3d_vector& c_3d_vector::operator=(const c_3d_vector& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}
	c_3d_vector::c_3d_vector(const c_3d_vector& other)
	{
		*this = other;
	}
	void c_3d_vector::set(float in_x, float in_y, float in_z)
	{
		//m_mtx.lock();
		{
			x = in_x;
			y = in_y;
			z = in_z;

			//m_magnitude = sqrtf(x * x + y * y + z * z);
			//
			//m_norm[0] = x / m_magnitude;
			//m_norm[1] = y / m_magnitude;
			//m_norm[2] = z / m_magnitude;
		}	
		//m_mtx.unlock();
	}
	xyz_t c_3d_vector::get()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			result[0] = x;
			result[1] = y;
			result[2] = z;
		}
		//m_mtx.unlock();

		return result;
	}
	float c_3d_vector::mangitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	xyz_t c_3d_vector::norm()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			float magnitude = sqrtf(x * x + y * y + z * z);
			result[0] = x / magnitude;
			result[1] = y / magnitude;
			result[2] = z / magnitude;
		}
		//m_mtx.unlock();

		return result;
	}
	void c_3d_vector::rotate_vector(c_3d_vector& vec, float angle, float u_x, float u_y, float u_z)
	{
		std::mutex mtx{};

		float x_ = vec.x;
		float y_ = vec.y;
		float z_ = vec.z;

		//mtx.lock();
		{
			angle = angle * pi_ / 180.0f;

			vec.x =
				u_x * (u_x * x_ + u_y * y_ + u_z * z_)
				- ((-1 + u_x * u_x) * x_ + u_x * (u_y * y_ + u_z * z_)) * cosf(angle)
				+ (-(u_z * y_) + u_y * z_) * sinf(angle);

			vec.y =
				u_y * (u_x * x_ + u_y * y_ + u_z * z_)
				- (u_x * u_y * x_ + (-1 + u_y * u_y) * y_ + u_y * u_z * z_) * cosf(angle)
				+ (u_z * x_ - u_x * z_) * sinf(angle);

			vec.z =
				u_z * (u_x * x_ + u_y * y_ + u_z * z_)
				- (u_x * u_z * x_ + u_y * u_z * y_ + (-1 + u_z * u_z) * z_) * cosf(angle)
				+ (-(u_y * x_) + u_x * y_) * sinf(angle);
		}
		//mtx.unlock();
	}
	c_3d_vector c_3d_vector::cross(const c_3d_vector& other)
	{
		c_3d_vector a{};
		c_3d_vector b{};
		c_3d_vector c{};
		//m_mtx.lock();
		{
			a = *this;
			b = other;

			c.x = a.y * b.z - a.z * b.y;
			c.y = a.z * b.x - a.x * b.z;
			c.z = a.x * b.y - a.y * b.x;
		}
		//m_mtx.unlock();

		return c;
	}
}