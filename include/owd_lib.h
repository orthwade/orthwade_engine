#pragma once
#include <owd_misc.h>
#include <owd_math.h>
#include <owd_strings.h>
#include <owd_time.h>
#include <owd_debug.h>
#include <owd_sound.h>
#include <owd_filesystem.h>
#include <owd_graphics.h>
#include <owd_input.h>

#ifndef owd_lib_link
#define owd_lib_link
#ifdef _DEBUG
#pragma comment(lib,"x64/Debug/owd_misc.lib")
#pragma comment(lib,"x64/Debug/owd_math.lib")
#pragma comment(lib,"x64/Debug/owd_strings.lib")
#pragma comment(lib,"x64/Debug/owd_time.lib")
#pragma comment(lib,"x64/Debug/owd_debug.lib")
#pragma comment(lib,"x64/Debug/owd_sound.lib")
#pragma comment(lib,"x64/Debug/owd_filesystem.lib")
#pragma comment(lib,"x64/Debug/owd_graphics.lib")
#pragma comment(lib,"x64/Debug/owd_input.lib")
#else
#pragma comment(lib,"x64/Release/owd_misc.lib")
#pragma comment(lib,"x64/Release/owd_math.lib")
#pragma comment(lib,"x64/Release/owd_strings.lib")
#pragma comment(lib,"x64/Release/owd_time.lib")
#pragma comment(lib,"x64/Release/owd_debug.lib")
#pragma comment(lib,"x64/Release/owd_sound.lib")
#pragma comment(lib,"x64/Release/owd_filesystem.lib")
#pragma comment(lib,"x64/Release/owd_graphics.lib")
#pragma comment(lib,"x64/Release/owd_input.lib")
#endif
#endif // !owd_lib_link

