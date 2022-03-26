#include "c_geom_triangle.h"

namespace owd_lib
{
    c_geom_triangle::c_geom_triangle()
    {

    }
    c_geom_triangle::c_geom_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3)
    {
        set_vertices({ x_1, y_1, x_2, y_2, x_3, y_3 });
    }
}

