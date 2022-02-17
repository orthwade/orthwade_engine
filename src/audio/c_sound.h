#pragma once
//#include "c_wav_file.h"
#include "c_sound_buffer.h"
#include "c_sound_device.h"
#include "ogg/ogg_.h"
#include "openal/openal.h"

namespace owd
{
	/// <summary>
	/// c_sound class
	/// </summary>
	class c_sound : public c_basic_object
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		c_sound();
		/// <summary>
		/// 
		/// </summary>
		/// <param name="file_path"></param>
		~c_sound();

		bool load(std::wstring_view file_path);
		bool load(std::wstring_view file_path, std::wstring_view name);

		c_sound_buffer* buffer();

		inline	size_t		samples_count			() { return m_ogg.samples_count				(); }
		inline	uint32_t	channels_count			() { return m_ogg.channels_count			(); }
		inline	uint32_t	sample_rate				() { return m_ogg.sample_rate				(); }
		inline	uint32_t	bits_per_sample			() { return m_ogg.bits_per_sample			(); }
		inline	uint32_t	sound_data_bytes_count	() { return m_ogg.sound_data_bytes_count	(); }

		inline byte_t* sound_data_ptr()	{ return m_ogg.sound_data_ptr(); }
		inline std::wstring_view filepath() { return m_ogg.filepath(); }

		bool good() const override;

	private:
		c_ogg_file m_ogg{};
		
		c_sound_buffer m_sound_buffer{};

		bool m_set_data();

		bool m_good = false;

	};
}
