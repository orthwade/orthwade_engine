#include "c_listener.h"

namespace owd_lib
{
	c_listener* c_listener::m_singleton = nullptr;
	
	void c_listener::set_position(float x, float y, float z)
	{
		//m_mtx.lock();
		{
			m_logger << "setting position x: " << x << ";    y: " << y << ";    z: " << z << '\n';
			m_x = x;
			m_y = y;
			m_z = z;
			AL_CALL(alListener3f(AL_POSITION, x, y, z));
		}
		//m_mtx.unlock();
	}
	void c_listener::set_gain(float gain)
	{
		//m_mtx.lock();
		{
			m_logger << "setting gain: " << gain << '\n';

			if (gain < 0.0f)
			{
				gain = 0.0f;
			}

			m_gain = gain;

			AL_CALL(alListenerf(AL_GAIN, gain));
		}
		//m_mtx.unlock();
	}
	void c_listener::set_velocity(float x, float y, float z)
	{
		//m_mtx.lock();
		{
			m_logger << "setting velocity x: " << x << ";    y: " << y << ";    z: " << z << '\n';
			m_velocity_x = x;
			m_velocity_y = y;
			m_velocity_z = z;
			AL_CALL(alListener3f(AL_VELOCITY, x, y, z));
		}
		//m_mtx.unlock();
	}
	xyz_t c_listener::position()
	{
		xyz_t result{};
		//m_mtx.lock();
		{
			m_logger << "getting position\n";

			AL_CALL(alGetListener3f(AL_POSITION, &m_x, &m_y, &m_z));

			result = { m_x, m_y, m_z };
		}
		//m_mtx.unlock();
		return result;
	}
	xyz_t c_listener::orientation_at()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			m_logger << "getting orientation \"AT\"\n";

			AL_CALL(alGetListenerfv(AL_ORIENTATION, m_ori.ori.data()));

			result = { m_ori.ori[0], m_ori.ori[1], m_ori.ori[2] };
			m_ori.update_from_public_array();
		}
		//m_mtx.unlock();

		return result;
	}
	xyz_t c_listener::orientation_up()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			m_logger << "getting orientation \"UP\"\n";

			AL_CALL(alGetListenerfv(AL_ORIENTATION, m_ori.ori.data()));

			result = { m_ori.ori[3], m_ori.ori[4], m_ori.ori[5] };
			m_ori.update_from_public_array();
		}
		//m_mtx.unlock();

		return result;
	}
	ori_t c_listener::orientation()
	{
		ori_t result{};

		//m_mtx.lock();
		{
			m_logger << "getting orientation \"UP\"\n";

			AL_CALL(alGetListenerfv(AL_ORIENTATION, m_ori.ori.data()));

			result = m_ori.ori;
			m_ori.update_from_public_array();
		}
		//m_mtx.unlock();

		return result;
	}
	void c_listener::rotate(float v, float h, float r)
	{
		//m_mtx.lock();
		{
			m_logger << "rotate orientation\n";

			m_ori.rotate(v, h, r);

			AL_CALL(alListenerfv(AL_ORIENTATION, m_ori.ori.data()));
		}
		//m_mtx.unlock();
	}
	void c_listener::rotate_(float v, float h, float r)
	{
		//m_mtx.lock();
		{
			m_logger << "rotate orientation around original axes\n";

			m_ori.rotate_(v, h, r);

			AL_CALL(alListenerfv(AL_ORIENTATION, m_ori.ori.data()));
		}
		//m_mtx.unlock();
	}
	void c_listener::set_default_orientation()
	{
		//m_mtx.lock();
		{
			m_logger << "setting orientation to default\n";

			m_ori.set_default();

			AL_CALL(alListenerfv(AL_ORIENTATION, m_ori.ori.data()));

		}
		//m_mtx.unlock();
	}
	float c_listener::gain()
	{
		float result{};

		//m_mtx.lock();
		{
			m_logger << "getting position\n";

			AL_CALL(alGetListenerf(AL_GAIN, &m_gain));

			result = m_gain;
		}
		//m_mtx.unlock();

		return result;
	}
	c_listener::c_listener()
	{
		m_logger << "----openal_listener constructor START----\n";
		set_name(L"listenet_object");
		set_logger_name(L"listener_logger");
		//set_gain(1.0f);
		//set_position(0.0f, 0.0f, 0.0f);
		//set_velocity(0.0f, 0.0f, 0.0f);
		m_logger << "----openal_listener constructor SUCCESS----\n";
	}

	c_listener* owd_lib::c_listener::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_listener();
		}

		return m_singleton;
	}
	void c_listener::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
    c_listener::~c_listener()
    {
    }
}
