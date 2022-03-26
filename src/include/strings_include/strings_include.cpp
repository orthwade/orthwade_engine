#include "strings_include.h"
#include "../../strings/compare_strings.h"

namespace owd
{
	bool strings_are_equal(std::wstring_view one, std::wstring_view two)
	{
		return owd_lib::strings_are_equal(one, two);
	}
}