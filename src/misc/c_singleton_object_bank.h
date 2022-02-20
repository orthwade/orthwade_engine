//#pragma once
//#include "c_singleton.h"
//#include "c_basic_object.h"
//
//namespace owd
//{
//	template <class T>
//	class c_singleton_object_bank : public c_singleton<c_singleton_object_bank<T>>
//	{
//	public:
//
//		inline void set_name(std::wstring_view name) { m_name = name; }
//		inline void set_logger_name(std::wstring_view name) { m_logger.set_name(name); }
//
//		inline std::wstring_view name() { return m_name; }
//
//		void add(const T& object);
//		void add(std::shared_ptr<T>& object);
//
//		std::shared_ptr<T>& by_index(uint64_t i);
//		std::shared_ptr<T>& by_name(std::wstring_view name);
//
//		void clear();
//
//		void erase(uint64_t index);
//		void erase(std::wstring_view name);
//
//		virtual inline size_t size_bytes() const { return m_vec_objects.size(); }
//
//		inline size_t count() { return m_vec_objects.size(); }
//
//	protected:
//		c_singleton_object_bank();
//
//		std::wstring m_name{ L"singleton_object_bank_object" };
//
//		c_logger m_logger{ L"singleton_object_bank_logger" };
//
//		std::vector<std::shared_ptr<T>> m_vec_objects{};
//
//		bool check_double(const T& object);
//	};
//}