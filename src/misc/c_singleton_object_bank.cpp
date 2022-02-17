#include "c_singleton_object_bank.h"

namespace owd
{
    template<class T>
    c_singleton_object_bank<T>::c_singleton_object_bank()
    {
    }
   
    template<class T>
    void c_singleton_object_bank<T>::add(const T& object)
    {
        m_logger << "----Adding object " << object.name() << " START----\n";
        {
            if (object.good())
            {
                if (check_double(object))
                {
                    auto object_shared_ptr = std::make_shared<T>(new T(object));
                    m_vec_objects.push_back(object_shared_ptr);
                    m_logger << "----Adding object " << object.name() << "SUCCESS----\n";
                }
                else
                {
                    m_logger << "----Adding object " << object.name() << " ERROR: found double----\n";
                }
            }
            else
            {
                m_logger << "----Adding object " << object.name() << " ERROR: the object has ERRORs----\n";
            }
        }
        m_logger << "----Adding object " << object.name() << " END----\n";
    }
    template<class T>
    void c_singleton_object_bank<T>::add(std::shared_ptr<T>& object)
    {
        m_logger << "----Adding object " << object->name() << " START----\n";
        {
            if (object->good())
            {
                if (check_double(*object))
                {
                    m_vec_objects.push_back(object);
                    m_logger << "----Adding object " << object->name() << "SUCCESS----\n";
                }
                else
                {
                    m_logger << "----Adding object " << object->name() << " ERROR: found double----\n";
                }
            }
            else
            {
                m_logger << "----Adding object " << object->name() << " ERROR: the object has ERRORs----\n";
            }
        }
        m_logger << "----Adding object " << object->name() << " END----\n";
    }
    template<class T>
    std::shared_ptr<T>& c_singleton_object_bank<T>::by_index(uint64_t i)
    {
        m_logger << "----Getting object by index: " << i << " START----\n";

        auto object = std::make_shared<T>();

        if (i < m_vec_objects.size())
        {
            object = m_vec_objects[i];
        }
        else
        {
            m_logger << "ERROR: index is out of scope\n";
        }

        return object;
    }
    template<class T>
    std::shared_ptr<T>& c_singleton_object_bank<T>::by_name(std::wstring_view name)
    {
        auto object = std::make_shared<T>();

        m_logger << "----Getting object by name: " << name << " START----\n";
        {
            if (m_vec_objects.empty())
            {
                m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                bool found = false;

                for (uint64_t i = 0; i != m_vec_objects.size(); ++i)
                {
                    if (m_vec_objects[i]->name() == name)
                    {
                        object = m_vec_objects[i];
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    m_logger << "object found\n";
                }
                else
                {
                    m_logger << "object NOT found\n";
                }
            }
        }
        m_logger << "----Getting object END----\n";

        return object;
    }

    template<class T>
    void c_singleton_object_bank<T>::clear()
    {
        m_logger << "----Clearing objectbank----\n";
        m_vec_objects.clear();
    }
    template<class T>
    void c_singleton_object_bank<T>::erase(uint64_t index)
    {
        m_logger << "----Erasing object at index: " << index << "----\n";
        {
            if (m_vec_objects.empty())
            {
                m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                if (index < m_vec_objects.size())
                {
                    auto iter = m_vec_objects.begin();

                    iter += index;

                    m_vec_objects.erase(iter);

                    m_logger << "----Erasing object OK----\n";
                }
                else
                {
                    m_logger << "ERROR: index is out of scope\n";
                }
            }
        }
        m_logger << "----Erasing object END----\n";
    }
    template<class T>
    void c_singleton_object_bank<T>::erase(std::wstring_view name)
    {
        m_logger << "----Erasing object by name: " << name << "----\n";
        {
            if (m_vec_objects.empty())
            {
                m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                auto iter = m_vec_objects.begin();
                uint64_t index = 0;
                bool found = false;

                for (uint64_t i = 0; i != m_vec_objects.size(); ++i)
                {
                    if (m_vec_objects[i]->name() == name)
                    {
                        found = true;
                        break;
                    }
                    ++index;
                }
                if (found)
                {
                    m_logger << "object found\n";
                }
                else
                {
                    m_logger << "object NOT found\n";
                }

                iter += index;

                m_vec_objects.erase(iter);

                m_logger << "----Erasing object OK----\n";
            }
        }
        m_logger << "----Erasing object END----\n";
    }
    template<class T>
    bool c_singleton_object_bank<T>::check_double(const T& object)
    {
        bool found_double = false;
        for (uint64_t i = 0; i != m_vec_objects.size(); ++i)
        {
            if (m_vec_objects[i]->name() == object.name())
            {
                found_double = true;
                break;
            }
        }
        return found_double;
    }
}