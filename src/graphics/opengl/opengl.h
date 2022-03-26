#pragma once

#define GLEW_STATIC

#include "glew.h"
//#include "eglew.h"
//#include "glxew.h"
//#include "wglew.h"

#include "glfw3.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")

#include "../../math/glm/glm.hpp"

namespace owd_lib
{
	typedef GLuint gl_index_t;
	typedef std::vector<gl_index_t> gl_indices_t;

	GLint gl_int32_param(GLenum param);
}

