#pragma once
#include "c_basic_object.h"

namespace owd_lib
{
	template <class T>
	class c_object_bank
	{
	public:
		c_object_bank();
		c_object_bank(std::wstring_view name);

		~c_object_bank();

		inline void set_name(std::wstring_view name) { this->m_name = name; }
		inline void set_logger_name(std::wstring_view name) { this->m_logger.set_name(name); }

		inline std::wstring_view name() { return this->m_name; }

		void add(const T& object);
		void add(std::shared_ptr<T>& object);

		std::shared_ptr<T>& by_index(uint64_t i);
		std::shared_ptr<T>& by_name(std::wstring_view name);

        std::shared_ptr<T>& first();
        std::shared_ptr<T>& last();


		void clear();

		void erase(uint64_t index);
		void erase(std::wstring_view name);

		virtual inline size_t size_bytes() const { return this->m_vec_objects.size(); }

		inline size_t count() { return this->m_vec_objects.size(); }

		inline bool empty() { return (this->count() > 0); }

		inline std::shared_ptr<T>& operator[](index_t i) { return this->by_index(i); }
		inline std::shared_ptr<T>& operator[](std::wstring_view name) { return this->by_name(name); }

	protected:
		std::wstring m_name{ L"object_bank_object" };
		
		c_logger m_logger{ L"object_bank_logger" };
		
		std::vector<std::shared_ptr<T>> m_vec_objects{};

		bool check_double(const T& object);
	};

    template<class T>
    c_object_bank<T>::c_object_bank()
    {
    }

    template<class T>
    c_object_bank<T>::c_object_bank(std::wstring_view name)
        :
        m_name(name)
    {
    }

    template<class T>
    c_object_bank<T>::~c_object_bank()
    {
    }

    template<class T>
    void c_object_bank<T>::add(const T& object)
    {
        //this->m_logger << "----Adding object " << object.name() << " START----\n";
        //{
        //    if (object.good())
        //    {
        //        if (this->check_double(object))
        //        {
        //            auto object_shared_ptr = std::make_shared<T>(new T(object));
        //            this->m_vec_objects.push_back(object_shared_ptr);
        //            this->m_logger << "----Adding object " << object.name() << "SUCCESS----\n";
        //        }
        //        else
        //        {
        //            this->m_logger << "----Adding object " << object.name() << " ERROR: found double----\n";
        //        }
        //    }
        //    else
        //    {
        //        this->m_logger << "----Adding object " << object.name() << " ERROR: the object has ERRORs----\n";
        //    }
        //}
        //this->m_logger << "----Adding object " << object.name() << " END----\n";
    }
    template<class T>
    void c_object_bank<T>::add(std::shared_ptr<T>& object)
    {
        this->m_logger << "----Adding object " << object->name() << " START----\n";
        {
            if (object->good())
            {
                if (this->check_double(*object))
                {
                    this->m_vec_objects.push_back(object);
                    this->m_logger << "----Adding object " << object->name() << "SUCCESS----\n";
                }
                else
                {
                    this->m_logger << "----Adding object " << object->name() << " ERROR: found double----\n";
                }
            }
            else
            {
                this->m_logger << "----Adding object " << object->name() << " ERROR: the object has ERRORs----\n";
            }
        }
        this->m_logger << "----Adding object " << object->name() << " END----\n";
    }
    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::by_index(uint64_t i)
    {
        this->m_logger << "----Getting object by index: " << i << " START----\n";

        auto object = std::make_shared<T>();

        if (i < this->m_vec_objects.size())
        {
            object = this->m_vec_objects[i];
        }
        else
        {
            this->m_logger << "ERROR: index is out of scope\n";
        }

        return object;
    }
    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::by_name(std::wstring_view name)
    {
        auto object = std::make_shared<T>();

        this->m_logger << "----Getting object by name: " << name << " START----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                bool found = false;

                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
                {
                    if (this->m_vec_objects[i]->name() == name)
                    {
                        object = this->m_vec_objects[i];
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    this->m_logger << "object found\n";
                }
                else
                {
                    this->m_logger << "object NOT found\n";
                }
            }
        }
        this->m_logger << "----Getting object END----\n";

        return object;
    }

    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::first()
    {
        if (m_vec_objects.empty())
        {
            auto empty = std::make_shared<T>();
            return empty;
        }
        else
        {
            return m_vec_objects.front();
        }
    }

    template<class T>
    std::shared_ptr<T>& c_object_bank<T>::last()
    {
        if (m_vec_objects.empty())
        {
            auto empty = std::make_shared<T>();
            return empty;
        }
        else
        {
            return m_vec_objects.back();
        }
    }

    template<class T>
    void c_object_bank<T>::clear()
    {
        this->m_logger << "----Clearing objectbank----\n";
        this->m_vec_objects.clear();
    }
    template<class T>
    void c_object_bank<T>::erase(uint64_t index)
    {
        this->m_logger << "----Erasing object at index: " << index << "----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                if (index < this->m_vec_objects.size())
                {
                    auto iter = this->m_vec_objects.begin();

                    iter += index;

                    this->m_vec_objects.erase(iter);

                    this->m_logger << "----Erasing object OK----\n";
                }
                else
                {
                    this->m_logger << "ERROR: index is out of scope\n";
                }
            }
        }
        this->m_logger << "----Erasing object END----\n";
    }
    template<class T>
    void c_object_bank<T>::erase(std::wstring_view name)
    {
        this->m_logger << "----Erasing object by name: " << name << "----\n";
        {
            if (this->m_vec_objects.empty())
            {
                this->m_logger << "ERROR: bank is empty\n";
            }
            else
            {
                auto iter = this->m_vec_objects.begin();
                uint64_t index = 0;
                bool found = false;

                for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
                {
                    if (this->m_vec_objects[i]->name() == name)
                    {
                        found = true;
                        break;
                    }
                    ++index;
                }
                if (found)
                {
                    this->m_logger << "object found\n";
                }
                else
                {
                    this->m_logger << "object NOT found\n";
                }

                iter += index;

                this->m_vec_objects.erase(iter);

                this->m_logger << "----Erasing object OK----\n";
            }
        }
        this->m_logger << "----Erasing object END----\n";
    }
    template<class T>
    bool c_object_bank<T>::check_double(const T& object)
    {
        bool found_double = false;
        for (uint64_t i = 0; i != this->m_vec_objects.size(); ++i)
        {
            if (this->m_vec_objects[i]->name() == object.name())
            {
                found_double = true;
                break;
            }
        }
        return found_double;
    }

}