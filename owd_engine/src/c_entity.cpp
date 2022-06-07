#include "c_entity.h"

namespace owd
{
    static auto lambda_set_srand = []()
    {
        std::srand(std::time(nullptr));
        return int32_t();
    };

    static auto set_srand_result = lambda_set_srand();

    static float constexpr static_float_rand_max = RAND_MAX;

    entity_t make_entity_buffer{};

    c_entity::c_entity(float x, float y, float width, float height,
        float red, float green, float blue, float alpha, uint16_t level)
        :
        m_x(x),
        m_y(y),
        m_w(width),
        m_h(height)
    {
        auto unit = std::make_shared<c_graphic_unit>(x, y, width, height, red, green, blue, alpha, level);
        m_units.push_back(unit);
    }
    c_entity::c_entity(float x, float y, float radius, 
        float red, float green, float blue, float alpha, uint16_t level)
        :
        m_x(x),
        m_y(y),
        m_w(radius),
        m_h(radius)
    {
        auto unit = std::make_shared<c_graphic_unit>(x, y, radius, red, green, blue, alpha, level);
        m_units.push_back(unit);
    }
    c_entity::c_entity
    (float x, float y, float w, float h, std::wstring_view texture_name, uint16_t level)
    {
        auto unit = std::make_shared<c_graphic_unit>(x, y, w, h, texture_name, level);
        m_units.push_back(unit);
    }
    std::shared_ptr<c_entity> c_entity::make
    (float x, float y, float w, float h, float r, float g, float b, float a, uint16_t l)
    {
        auto entity = std::make_shared<c_entity>(x, y, w, h, r, g, b, a, l);
        return entity;
    }
    c_entity::~c_entity()
    {
        if (m_lifetime_thread.joinable())
        {
            m_lifetime_thread.join();
        }
    }
    bool c_entity::point_is_inside(float x, float y)
    {
        float x_1 = m_x - m_w / 2.0f;
        float x_2 = m_x + m_w / 2.0f;
        float y_1 = m_y - m_h / 2.0f;
        float y_2 = m_y + m_h / 2.0f;

        if
        (
            x > x_1 &&
            x < x_2 &&
            y > y_1 &&
            y < y_2 
        )
        {
            return true;
        }

        return false;
    }
    void c_entity::resize(float multiplier)
    {
        m_x *= multiplier;
        m_y *= multiplier;
        for (auto& unit : m_units)
        {
            unit->resize(multiplier);
        }
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
    void c_entity::set_velocity(float x, float y)
    {
        m_v = { x, y };
    }
    void c_entity::set_acceleration(float x, float y)
    {
        m_a = { x, y };
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
    void c_entity::move_one_tick(float ticktime_ms)
    {
        float ticktime_ = ticktime_ms / 1000.0f;
        float delta_x = ticktime_ * (velocity().x + acceleration().x * ticktime_ / 2.0f);
        float delta_y = ticktime_ * (velocity().y + acceleration().y * ticktime_ / 2.0f);
        move(delta_x, delta_y);
        set_velocity
        (
            velocity().x + acceleration().x * ticktime_,
            velocity().y + acceleration().y * ticktime_
        );
    }
    float c_entity::lifetime() const
    {
        return m_lifetime_ms;
    }
    bool c_entity::lifetime_out()
    {
        bool result = false;
        if (m_lifetime_ms == std::numeric_limits<float>::infinity())
        {

        }
        else
        {
            result = m_lifetime_out;
        }
        return result;
    }
    void c_entity::start_async_lifetimer()
    {
        if (m_lifetime_ms != std::numeric_limits<float>::infinity())
        {
            m_lifetime_thread = std::thread
            (
                [&]() 
                {
                    sleep_for_ms(m_lifetime_ms);
                    m_lifetime_out = true;
                }
            );
        }
    }
   
    static xy_t static_gravity{ 0.0f, -2.0f / 16.0f };
    xy_t gravity()
    {
        return static_gravity;
    }
}

