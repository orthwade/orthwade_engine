#pragma once
#include "../../graphics/c_graphic_engine.h"

namespace owd
{
	using namespace owd_lib;
	typedef uint64_t index_t;
	/// <summary>
	/// Create window.
	/// </summary>
	void init();

	void run();

	/// <summary>
	/// Close window.
	/// </summary>
	void terminate();

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
		float red, float green, float blue, float alpha, uint16_t level);

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
		std::wstring_view texture_filepath, uint16_t level);

	/// <summary>
	/// Moves centre of graphic unit with index = unit_index to position [centre_x, centre_y].
	/// </summary>
	/// <param name="unit_index"></param>
	/// <param name="centre_x"></param>
	/// <param name="centre_y"></param>
	void set_graphic_unit_position(index_t unit_index, float centre_x, float centre_y);

	/// <summary>
	/// Move centre of textured graphic unit with index = unit_index to position [centre_x, centre_y].
	/// </summary>
	/// <param name="unit_index"></param>
	/// <param name="centre_x"></param>
	/// <param name="centre_y"></param>
	void set_textured_graphic_unit_position(index_t unit_index, float centre_x, float centre_y);

	/// <summary>
	/// Delete graphic unit with index = unit_index.
	/// </summary>
	/// <param name="unit_index"></param>
	void delete_graphic_unit(index_t unit_index);

}
