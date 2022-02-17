#include "s_rect.h"

namespace owd
{
	namespace geom
	{
		vertices_t s_rect::vertices()
		{
			return
			{
				bottom_left_x()	,	bottom_left_y()		,
				bottom_right_x(),	bottom_right_y()	,
				top_right_x()	,	top_right_y()		,
				top_left_x()	,	top_left_y()
			};
		}
	}
    
}

