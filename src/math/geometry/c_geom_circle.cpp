#include "c_geom_circle.h"

namespace owd_lib
{
    c_geom_circle::c_geom_circle()
        :c_geom_circle(0.0f, 0.0f, 0.1f)
    {
    }
    c_geom_circle::c_geom_circle(float x, float y, float r)
        :
        m_x(x), m_y(y), m_r(r)
    {
        float angle_step = 360.0f / m_triangles_count;
        float angle = 90.0f + angle_step / 2.0f;

        for (uint16_t i = 0; i != m_triangles_count + 1; ++i)
        {
            xy_t xy{ m_x + m_r * cos_d(angle), m_y + m_r * sin_d(angle) };
            m_vertices.push_back(xy.x);
            m_vertices.push_back(xy.y);
            angle += angle_step;
        }
    }
    c_geom_circle::~c_geom_circle()
    {
    }
    float c_geom_circle::radius() const
    {
        return m_r;
    }
    void c_geom_circle::set(float centre_x, float centre_y, float radius)
    {
        m_x = centre_x;
        m_y = centre_y;
        m_r = radius;

        float angle_step = 360.0f / m_triangles_count;
        float angle = 90.0f + angle_step / 2.0f;

        m_vertices.clear();

        for (uint16_t i = 0; i != m_triangles_count + 1; ++i)
        {
            xy_t xy{ m_x + m_r * cos_d(angle), m_y + m_r * sin_d(angle) };
            m_vertices.push_back(xy.x);
            m_vertices.push_back(xy.y);
            angle += angle_step;
        }
    }
}

