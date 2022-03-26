#pragma once
#include "../debug/logger/logger.h"

namespace owd_lib
{
	class c_basic_object
	{
	public:
		c_basic_object(std::wstring_view name);
		c_basic_object();

		virtual void reset();
		
		inline void set_name(std::wstring_view name) { m_name = name; }
		
		inline std::wstring_view name() const { return m_name; }

		virtual bool good() const;

		void set_logger_name(std::wstring_view name);
		void set_logger_mode(enm_log_mode mode);

		inline data_t & data() { return m_data_shared_ptr; }
		inline byte_t* data_raw_ptr() { return data()->data(); }

		virtual inline size_t size_bytes() const { return m_data_shared_ptr->size(); }

	protected:
		std::wstring m_name{ L"basic_object" };

		c_logger m_logger{ L"basic_object_logger" };

		data_t m_data_shared_ptr = std::make_shared<bytes_t>();

		inline bool default_good() const { return m_good; }

	private:
		bool m_good = true;
	};
}