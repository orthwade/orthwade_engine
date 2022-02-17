#pragma once
#include "logger/logger.h"
#include "../audio/openal/openal.h"

#define AL_CALL(x) \
al_clear_error(); \
x;\
ASSERT(al_log_call())

namespace owd
{
	static c_logger al_logger{ L"al_logger" };
	static std::wstring al_error_str{};
	static void al_clear_error()
	{
		while (alGetError() != AL_NO_ERROR)
		{

		}
	}
	static bool al_log_call()
	{
		while (ALenum error = alGetError())
		{
			switch (error)
			{
			case AL_INVALID_NAME	 : 
				al_error_str = L"[AL_INVALID_NAME] a bad name(ID) was passed to an OpenAL function";					
				break;
			case AL_INVALID_ENUM	 : 
				al_error_str = L"[AL_INVALID_ENUM] an invalid enum value was passed to an OpenAL function";					
				break;;
			case AL_INVALID_VALUE	 : 
				al_error_str = L"[AL_INVALID_VALUE] an invalid value was passed to an OpenAL function";		
				break;;
			case AL_INVALID_OPERATION: 
				al_error_str = L"[AL_INVALID_OPERATION] the requested operation is not valid";				
				break;;
			case AL_OUT_OF_MEMORY	 : 
				al_error_str	= L"[AL_OUT_OF_MEMORY] the requested operation resulted in OpenAL running out of memory"; 
				break;
			default: 
				al_error_str = L"uknown error";
				break;

			}
			al_logger << L"----Openal call ERROR:\n" << al_error_str << "----\n";
			return false;
		}
		al_logger << L"----Openal call SUCCESS----\n";
		return true;
	}
}