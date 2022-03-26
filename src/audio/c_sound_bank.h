#pragma once
#include "c_sound.h"
#include "../misc/c_object_bank.h"

namespace owd_lib
{
	class c_sound_bank : public c_object_bank<c_sound>
	{
	public:
		bool load(std::wstring_view filepath);
		bool load(std::wstring_view filepath, std::wstring_view name);

		std::shared_ptr<c_sound>& by_filepath(std::wstring_view filepath);

		void erase_by_filepath(std::wstring_view filepath);

		static c_sound_bank* get_instance();
		static void terminate();

	protected:
		static c_sound_bank* m_singleton;

		c_sound_bank();
		~c_sound_bank();

		c_sound_bank(const c_sound_bank&) = delete;
		c_sound_bank& operator=(const c_sound_bank&) = delete;

	};
}