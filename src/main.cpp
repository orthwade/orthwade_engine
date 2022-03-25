#include "include/graphics_include/graphics_include.h"


int main()
{
	owd::init();

	owd::add_graphic_unit(0.5f, 0.1f, 0.15f, 0.9f, 0.2f, 0.3f, 0.5f, 1.0f, 1);
	auto textured_unit_1 = owd::add_graphic_unit(0.0f, 0.0f, 0.1f, 0.1f, L"rsc/textures/e_green.png", 2);
	owd::set_textured_graphic_unit_position(textured_unit_1, -0.5f, 0.0f);
	owd::delete_graphic_unit(textured_unit_1);
	owd::run();


	return 0;
}