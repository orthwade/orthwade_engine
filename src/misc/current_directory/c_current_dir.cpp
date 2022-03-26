#include "c_current_dir.h"

namespace owd_lib
{
	c_current_dir::c_current_dir()
	{
		auto current_path = std::filesystem::current_path();
		m_str = current_path.wstring();
	}

	c_current_dir::~c_current_dir()
	{
	}

	std::wstring_view c_current_dir::operator()()
	{
		return m_str;
	}

}


