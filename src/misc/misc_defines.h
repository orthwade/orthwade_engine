#pragma once
#include <vector>
#include <memory>
#include <array>
#include <thread>

namespace owd_lib
{
	typedef uint8_t byte_t;
	typedef uint64_t index_t;
	typedef std::vector<uint8_t> bytes_t;
	typedef std::shared_ptr<bytes_t> data_t;
	typedef std::array<float, 3> xyz_t; // array of space coordinates in Cartesian coordinate system

	/// <summary>
	/// array of orientaion coordinates in Cartesian coordinate system, 
	/// elements 0-2 are vector pointing where the object is "looking at"
	/// elements 3-5 are vector pointing whre the top of the object is pointing
	/// </summary>
	typedef std::array<float, 6> ori_t;
	constexpr float pi_ = 3.14159265358979324f;

	class c_thread
	{
	public:
		c_thread()
		{

		}
		std::thread& operator()()
		{
			return m_thread;
		}
		c_thread(const c_thread&)
		{

		}
		c_thread& operator=(const c_thread&)
		{

		}
	private:
		std::thread m_thread{};
	};

	template<class T>
	static std::shared_ptr<T> static_s_ptr;

	template<class T>
	std::shared_ptr<T>& empty_s_ptr_ref()
	{
		static_s_ptr = std::make_shared<T>();
		return static_s_ptr;
	}
	float cos_d(float angle_degrees);
	float sin_d(float angle_degrees);
}


