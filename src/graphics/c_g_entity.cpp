#include "c_g_entity.h"

namespace owd
{
    c_g_entity::c_g_entity()
    {
       
    }

   c_g_entity::~c_g_entity()
    {
      
    }

   inline bool c_g_entity::should_draw()
   {
       return m_should_draw;
   }

    /*c_g_entity::c_g_entity(const c_g_entity& other)
    {
       
    }

    c_g_entity& owd::c_g_entity::operator=(const c_g_entity& other)
    {
        if (this != &other)
        {
            m_name = other.m_name;
            m_logger = other.m_logger;
        }
        return *this;
    }*/
}

