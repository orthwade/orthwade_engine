#include "s_xy.h"

namespace owd_lib
{
    namespace geom
    {
        s_2d_coordinates_cartesian::s_2d_coordinates_cartesian()
        {
        }
        s_2d_coordinates_cartesian::s_2d_coordinates_cartesian(float x_, float y_)
            :
            x(x_),
            y(y_)
        {
        }
        s_2d_coordinates_cartesian s_2d_coordinates_cartesian::operator+(const s_2d_coordinates_cartesian& other)
        {
            xy_t result{};
            result.x = this->x + other.x;
            result.y = this->y + other.y;
            return result;
        }
        s_2d_coordinates_cartesian& s_2d_coordinates_cartesian::operator+=(const s_2d_coordinates_cartesian& other)
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }
        s_2d_coordinates_cartesian s_2d_coordinates_cartesian::operator-(const s_2d_coordinates_cartesian& other)
        {
            xy_t result{};
            result.x = this->x - other.x;
            result.y = this->y - other.y;
            return result;
        }
        s_2d_coordinates_cartesian& s_2d_coordinates_cartesian::operator-=(const s_2d_coordinates_cartesian& other)
        {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }
        s_2d_coordinates_cartesian s_2d_coordinates_cartesian::operator*(float multilpier)
        {
            xy_t result{};
            result.x = this->x * multilpier;
            result.y = this->y * multilpier;
            return result;
        }
        s_2d_coordinates_cartesian& s_2d_coordinates_cartesian::operator*=(float multilpier)
        {
            this->x *= multilpier;
            this->y *= multilpier;
            return *this;
        }
        s_2d_coordinates_cartesian s_2d_coordinates_cartesian::operator/(float divisor)
        {
            xy_t result{};
            result.x = this->x / divisor;
            result.y = this->y / divisor;
            return result;
        }
        s_2d_coordinates_cartesian& s_2d_coordinates_cartesian::operator/=(float divisor)
        {
            this->x /= divisor;
            this->y /= divisor;
            return *this;
        }
    }
}

