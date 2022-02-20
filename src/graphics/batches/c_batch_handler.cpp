#include "c_batch_handler.h"

namespace owd
{
    s_level& c_batch_handler::get_level(uint16_t level)
    {
        if (level < m_levels.size())
        {
        }
        else
        {
            m_levels.resize(static_cast<size_t>(level) + 1);
        }
        return m_levels[level];
    }
}

