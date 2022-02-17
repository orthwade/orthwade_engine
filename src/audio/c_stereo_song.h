#pragma once
#include "c_sound.h"
#include "c_sound_source.h"

namespace owd
{
	class c_stereo_song
	{
	public:
		c_stereo_song();
		c_stereo_song(c_sound* left, c_sound* right);
		~c_stereo_song();

		c_stereo_song(const c_stereo_song& other);
		c_stereo_song& operator=(const c_stereo_song& other);

		void play();

	private:
		c_sound* m_left{};
		c_sound* m_right{};

		c_sound_source m_source_left{};
		c_sound_source m_source_right{};

		std::mutex m_mtx{};

		c_logger m_logger{ L"stereo_song" };
	};
}


