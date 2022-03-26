#include "graphics_include.h"

void owd::init()

{
	auto graphic_engine = c_graphic_engine::get_instance();
}

void owd::run()
{
	auto graphic_engine = c_graphic_engine::get_instance();
	graphic_engine->run();
}
void owd::terminate()
{
	auto graphic_engine = c_graphic_engine::get_instance();
	graphic_engine->terminate();
}
uint64_t owd::add_graphic_unit(float centre_x, float centre_y, float width, float height, float red, float green, float blue, float alpha, uint16_t level)
{
	auto graphic_engine = c_graphic_engine::get_instance();
	auto& batch_handler = graphic_engine->get_batch_handler();
	return batch_handler.add_rect(centre_x, centre_y, width, height, red, green, blue, alpha, level);
}

uint64_t owd::add_graphic_unit(float centre_x, float centre_y, float width, float height, std::wstring_view texture_filepath, uint16_t level)
{
	auto& graphic_engine = *c_graphic_engine::get_instance();
	auto texture = graphic_engine.load_and_get_texture(texture_filepath);
	auto& batch_handler = graphic_engine.get_batch_handler();
	return batch_handler.add_textured(centre_x, centre_y, width, height, texture, level);
}

void owd::set_graphic_unit_position(uint64_t unit_index, float centre_x, float centre_y)
{
	c_graphic_engine::get_instance()->get_batch_handler().get_unit_by_index(unit_index)->
		set_position(centre_x, centre_y);
}

void owd::set_textured_graphic_unit_position(uint64_t unit_index, float centre_x, float centre_y)
{
	c_graphic_engine::get_instance()->get_batch_handler().get_textured_unit_by_index(unit_index)->
		set_position(centre_x, centre_y);
}

void owd::delete_graphic_unit(uint64_t unit_index)
{
	c_graphic_engine::get_instance()->get_batch_handler().delete_by_index(unit_index);
}
