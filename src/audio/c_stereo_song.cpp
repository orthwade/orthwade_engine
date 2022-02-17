#include "c_stereo_song.h"

namespace owd
{
	c_stereo_song::c_stereo_song()
	{
	}
	c_stereo_song::c_stereo_song(c_sound* left, c_sound* right)
	{
		//m_mtx.lock();
		{
			m_left = left;
			m_right = right;
			
			m_source_left  = c_sound_source(L"left_channel", left);
			m_source_right = c_sound_source(L"right_channel", right);
			
			m_source_left.set_position(-1.1f, 0.0f, -1.1f);
			m_source_right.set_position(1.1f, 0.0f, -1.1f);
		}
		//m_mtx.unlock();
	}
	c_stereo_song::~c_stereo_song()
	{
	}
	c_stereo_song::c_stereo_song(const c_stereo_song& other)
	{
		*this = other;
	}
	c_stereo_song& c_stereo_song::operator=(const c_stereo_song& other)
	{
		if (this != &other)
		{
			//m_mtx.lock();
			{
				m_left = other.m_left;
				m_right = other.m_right;

				m_source_left  = other.m_source_left;
				m_source_right = other.m_source_right;
				m_logger = other.m_logger;
			}
			//m_mtx.unlock();
		}
		return *this;
	}
	void c_stereo_song::play()
	{
		////m_mtx.lock();
		{
			m_source_left.enable();
			m_source_right.enable();
		}
		////m_mtx.unlock();
	}
}