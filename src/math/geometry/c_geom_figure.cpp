#include "c_geom_figure.h"

namespace owd_lib
{
    c_geom_figure::c_geom_figure()
    {
    }
    c_geom_figure::c_geom_figure(const std::vector<float>& vertices)
        :
        m_vertices(vertices)
    {
        auto xy = centre(m_vertices);

        m_x = xy.x;
        m_y = xy.y;
    }
    c_geom_figure::~c_geom_figure()
    {
    }
    const std::vector<float>& c_geom_figure::vertices() const
    {
        return m_vertices;
    }
    void c_geom_figure::set_vertices(const std::vector<float>& vertices)
    {
        m_vertices = vertices;

        auto xy = centre(m_vertices);

        m_x = xy.x;
        m_y = xy.y;
    }
    xy_t c_geom_figure::centre(const std::vector<float>& vertices)
    {
        xy_t result{ 0.0f, 0.0f };

        size_t vertices_count = vertices.size() / 2;

        for (index_t i = 0; i < vertices_count; ++i, ++i)
        {
            result += { vertices[i], vertices[i + 1] };
        }

        result /= static_cast<float>(vertices_count);

        return result;
    }
    xy_t c_geom_figure::centre() const
    {
        return { m_x, m_y };
    }
}