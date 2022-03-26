#include "c_basic_object.h"

namespace owd_lib
{
    bool c_basic_object::good() const
    {
        return default_good();
    }
    void c_basic_object::set_logger_name(std::wstring_view name)
    {
        m_logger.set_name(name);
    }
    void c_basic_object::set_logger_mode(enm_log_mode mode)
    {
        m_logger.set_mode(mode);
    }
    c_basic_object::c_basic_object(std::wstring_view name)
        :
        m_name(name)
    {
    }
    c_basic_object::c_basic_object()
    {
    }
    void c_basic_object::reset()
    {
        *this = c_basic_object();
    }
}

