#include "audio/c_sound_engine.h"
#include "graphics/c_graphic_engine.h"
//#include "draughts/c_draughts.h"

auto static sound_engine   = owd::c_sound_engine  ::get_instance();
auto static graphic_engine = owd::c_graphic_engine::get_instance();

//auto static draughts = owd::c_draughts::get_instance();

int main()
{
	graphic_engine->enable_imgui(true);

	//auto& textured_objects = graphic_engine->get_batches_textured_rects();
	//graphic_engine->texture_by_filepath(L"rsc/textures")
	//auto& textu
	//textured_objects.add(0.0f, 0.0f, 0.5f, 0.5f, )
	
	graphic_engine->run();
	graphic_engine->terminate();
	sound_engine->terminate();
	return 0;
}