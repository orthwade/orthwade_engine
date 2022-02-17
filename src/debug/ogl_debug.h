#pragma once
#include "logger/logger.h"
#include "../graphics/opengl/opengl.h"

//static std::mutex gl_call_mtx{};

#define GL_CALL(x) \
gl_clear_error(); \
x;\
ASSERT(gl_log_call())

namespace owd
{
	static c_logger gl_logger{ L"gl_logger" };
	static std::wstring gl_error_str{};
	static std::wstring_view error_view(GLenum error_code)
	{
		std::wstring result{};
		switch (error_code)
		{
		case	GL_INVALID_ENUM:
			gl_error_str =
				L"[GL_INVALID_ENUM] An unacceptable value is specified for an enumerated argument.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_INVALID_VALUE:
			gl_error_str =
				L"[GL_INVALID_VALUE] A numeric argument is out of range.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_INVALID_OPERATION:
			gl_error_str =
				L"[GL_INVALID_OPERATION] The specified operation is not allowed in the current state.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

			//case	GL_NO_ERROR 			:
			//	gl_error_str =
			//		L"[GL_NO_ERROR] No error has been recorded.\n"
			//		"The value of this symbolic constant is guaranteed to be zero.\n";
			//	break;

		case	GL_STACK_OVERFLOW:
			gl_error_str =
				L"[GL_STACK_OVERFLOW] This function would cause a stack overflow.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_STACK_UNDERFLOW:
			gl_error_str =
				L"[GL_STACK_UNDERFLOW] This function would cause a stack underflow.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_OUT_OF_MEMORY:
			gl_error_str =
				L"[GL_OUT_OF_MEMORY] There is not enough memory left to execute the function.\n"
				"The state of OpenGL is undefined, except for the state of the error flags, after this error is recorded.\n";
			break;

		default:
			gl_error_str = L"uknown error";
			break;

		}
		return gl_error_str;
	}
	static void gl_clear_error()
	{
		//gl_call_mtx.lock();
		GLenum error{};
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			gl_error_str = error_view(error);
			if (error != GL_NO_ERROR)
			{
				gl_logger << L"----Opengl CLEAR ERRORS: ERROR_CODE: " << gl_error_str << '\n';
			}
			else
			{
				gl_logger << L"----Opengl CLEAR ERRORS: NO ERROR\n";
			}
		}
		//gl_call_mtx.unlock();
	}
	static bool gl_log_call()
	{
		//gl_call_mtx.lock();
		while (GLenum error = glGetError())
		{
			gl_error_str = error_view(error);
			if (error != GL_NO_ERROR)
			{
				gl_logger << L"----Opengl call ERROR: " << gl_error_str << '\n';
				//gl_call_mtx.unlock();
				return false;
			}
		}
		gl_logger << L"----Opengl call SUCCESS\n";
		//gl_call_mtx.unlock();
		return true;
	}
}