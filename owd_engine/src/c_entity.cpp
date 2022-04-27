#include "c_entity.h"

namespace owd
{
    entity_t make_entity_buffer{};

    c_entity::c_entity(float x, float y, float width, float height, 
        float red, float green, float blue, float alpha, uint16_t level)
        :
        m_x(x),
        m_y(y)
    {
        auto unit = std::make_shared<c_graphic_unit>(x, y, width, height, red, green, blue, alpha, level);
        m_units.push_back(unit);
    }
    c_entity::~c_entity()
    {
    }
    void c_entity::set_position(float x, float y)
    {
        m_x = x;
        m_y = y;
        for (auto& unit : m_units)
        {
            unit->set_position(x, y);
        }
    }
    void c_entity::move(float d_x, float d_y)
    {
        m_x += d_x;
        m_y += d_y;
        for (auto& unit : m_units)
        {
            unit->move(d_x, d_y);
        }
    }
}

