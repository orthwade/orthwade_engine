#include "c_sound.h"

namespace owd_lib
{
	c_sound::c_sound()
	{
		set_name(L"sound_object");
		set_logger_name(L"sound_object_logger");
	}
	
	c_sound::~c_sound()
	{
		m_sound_buffer.release();
	}

	bool c_sound::load(std::wstring_view filepath)
	{
		return load(filepath, filepath);
	}
	bool c_sound::load(std::wstring_view filepath, std::wstring_view name)
	{
		m_logger << m_name << '-' << "loading file: " << filepath << '\n';

		//m_ogg.load(filepath, name);

		if (m_ogg.load(filepath))
		{
			m_good = m_set_data();
		}

		return m_good;
	}
	c_sound_buffer* c_sound::buffer()
	{
		return &m_sound_buffer;
	}

	bool c_sound::good() const
	{
		return m_good;
	}

	bool c_sound::m_set_data()
	{
		bool result = false;
		ALenum format{};

		if (channels_count() == 1)
		{
			if (bits_per_sample() == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else if (bits_per_sample() == 16)
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else if (channels_count() == 2)
		{
			if (bits_per_sample() == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else if (bits_per_sample() == 16)
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		if (format == ALenum{})
		{
			m_logger << "----ERROR: Unsupporter format----\n";
		}
		else
		{
			result = true;
			m_sound_buffer.set_data(sound_data_ptr(), sound_data_bytes_count(), sample_rate(), format);
		}

		return result;
	}
}