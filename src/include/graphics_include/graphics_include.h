#pragma once
#include "../../graphics/c_graphic_engine.h"

namespace owd
{
	/// <summary>
	/// Create window.
	/// </summary>
	void init()
	{
		auto graphic_engine = c_graphic_engine::get_instance();
	}


	void run()
	{
		auto graphic_engine = c_graphic_engine::get_instance();
		graphic_engine->run();
	}

	/// <summary>
	/// Close window.
	/// </summary>
	void terminate()
	{
		auto graphic_engine = c_graphic_engine::get_instance();
		graphic_engine->terminate();
	}
	/// <summary>
	/// Add coloured rectangle and get its index.
	/// </summary>
	/// <param name="centre_x"></param>
	/// <param name="centre_y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="red"></param>
	/// <param name="green"></param>
	/// <param name="blue"></param>
	/// <param name="alpha"></param>
	/// <param name="level"></param>
	/// <returns></returns>
	index_t add_graphic_unit(float centre_x, float centre_y, float width, float height,
		float red, float green, float blue, float alpha, uint16_t level)
	{
		auto graphic_engine = c_graphic_engine::get_instance();
		auto& batch_handler = graphic_engine->get_batch_handler();
		return batch_handler.add_rect(centre_x, centre_y, width, height, red, green, blue, alpha, level);
	}

	/// <summary>
	/// Add coloured circle and get its index.
	/// </summary>
	/// <param name="centre_x"></param>
	/// <param name="centre_y"></param>
	/// <param name="radius"></param>
	/// <param name="red"></param>
	/// <param name="green"></param>
	/// <param name="blue"></param>
	/// <param name="alpha"></param>
	/// <param name="level"></param>
	/// <returns></returns>
	index_t add_graphic_unit(float centre_x, float centre_y, float radius,
		float red, float green, float blue, float alpha, uint16_t level)
	{
		auto graphic_engine = c_graphic_engine::get_instance();
		auto& batch_handler = graphic_engine->get_batch_handler();
		return batch_handler.add_circle(centre_x, centre_y, radius, red, green, blue, alpha, level);
	}

	/// <summary>
	/// Add textured rectangle and get its index.
	/// </summary>
	/// <param name="centre_x"></param>
	/// <param name="centre_y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="filepath"></param>
	/// <param name="level"></param>
	/// <returns></returns>
	index_t add_graphic_unit(float centre_x, float centre_y, float width, float height,
		std::wstring_view texture_filepath, uint16_t level)
	{
		auto& graphic_engine = *c_graphic_engine::get_instance();
		auto texture = graphic_engine.load_and_get_texture(texture_filepath);
		auto& batch_handler = graphic_engine.get_batch_handler();
		return batch_handler.add_textured(centre_x, centre_y, width, height, texture, level);
	}

	/// <summary>
	/// Moves centre of graphic unit with index = unit_index to position [centre_x, centre_y].
	/// </summary>
	/// <param name="unit_index"></param>
	/// <param name="centre_x"></param>
	/// <param name="centre_y"></param>
	void set_graphic_unit_position(index_t unit_index, float centre_x, float centre_y)
	{
		c_graphic_engine::get_instance()->get_batch_handler().get_unit_by_index(unit_index)->
			set_position(centre_x, centre_y);
	}
	/// <summary>
	/// Moves centre of textured graphic unit with index = unit_index to position [centre_x, centre_y].
	/// </summary>
	/// <param name="unit_index"></param>
	/// <param name="centre_x"></param>
	/// <param name="centre_y"></param>
	void set_textured_graphic_unit_position(index_t unit_index, float centre_x, float centre_y)
	{
		c_graphic_engine::get_instance()->get_batch_handler().get_textured_unit_by_index(unit_index)->
			set_position(centre_x, centre_y);
	}

	/// <summary>
	/// Delete graphic unit with index = unit_index.
	/// </summary>
	/// <param name="unit_index"></param>
	void delete_graphic_unit(index_t unit_index)
	{
		c_graphic_engine::get_instance()->get_batch_handler().delete_by_index(unit_index);
	}

}
