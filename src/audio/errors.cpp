//
//
//namespace owd
//{
//	std::wstring openal_error_string(ALCenum error)
//	{
//		std::wstring error_string{ L"default_error_string" };
//		switch (error)
//		{
//		case AL_NO_ERROR 		 : error_string = L""											; break;
//		case AL_INVALID_NAME 	 : error_string = L"OpenAL error code:  AL_INVALID_NAME"		; break;
//		case AL_INVALID_ENUM 	 : error_string = L"OpenAL error code:  AL_INVALID_ENUM"		; break;
//		case AL_INVALID_VALUE 	 : error_string = L"OpenAL error code:  AL_INVALID_VALUE"		; break;
//		case AL_INVALID_OPERATION: error_string = L"OpenAL error code:  AL_INVALID_OPERATION"	; break; 
//		case AL_OUT_OF_MEMORY	 : error_string = L"OpenAL error code:  AL_OUT_OF_MEMORY"		; break;
//		default:
//			error_string = L"Unknown error";
//			break;
//		}
//		return error_string;
//	}
//
//	c_openal_check::c_openal_check()
//	{
//		//m_mtx.lock();
//		{
//			m_openal_device_ptr = (c_sound_device::get_openal_device());
//		}
//		//m_mtx.unlock();
//	}
//	c_openal_check::c_openal_check(std::wstring_view name)
//	{
//		//m_mtx.lock();
//		{
//			m_name = std::wstring(name);
//			m_openal_device_ptr = (c_sound_device::get_openal_device());
//			std::wstring new_logger_name{};
//			new_logger_name = m_name + L" [openal_check]";
//			m_logger.set_name(new_logger_name);
//		}
//		//m_mtx.unlock();
//	}
//	c_openal_check::c_openal_check(const c_openal_check& other)
//		:c_openal_check(other.m_name)
//	{
//	}
//	
//	bool c_openal_check::operator()(std::wstring_view input)
//	{
//		std::wstring str = std::wstring(input);
//		bool result = false;
//		//m_mtx.lock();
//		{
//			m_error = alcGetError(m_openal_device_ptr);
//			//m_logger << openal_error_string(m_error) << '\n';
//			if (m_error == ALC_NO_ERROR)
//			{
//				m_logger << str << ": OpenAL check OK" << '\n';
//				result = true;
//			}
//			else
//			{
//				m_logger << "OpenAL check ERROR" << '\n';
//				m_logger << openal_error_string(m_error) << '\n';
//			}
//		}
//		//m_mtx.unlock();
//
//		return result;
//	}
//	void c_openal_check::set_name(std::wstring_view name)
//	{
//		m_name = name;
//	}
//	void c_openal_check::set_logger_name(std::wstring_view name)
//	{
//		m_logger.set_name(name);
//	}
//}