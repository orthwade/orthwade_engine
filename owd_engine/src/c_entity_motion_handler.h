#pragma once
#include <list>

#include "c_entity.h"

namespace owd
{
	class c_entity_motion_handler
	{
	public:
		template<class T>
		void add(T& entity);

		inline void set_tickrate(float tickrate) { m_tickrate = tickrate; m_tick_time = 1.0f / m_tickrate; }

		void move_one_tick();

		void clear();

		

		static c_entity_motion_handler* get_instance();
		static void terminate();
	
	protected:
		float m_tickrate = 60.0f;
		float m_tick_time = 1.0f / 60.0f;

		std::vector<c_entity*> m_vec_entities{};

		static c_entity_motion_handler* m_singleton;

		c_entity_motion_handler();
		~c_entity_motion_handler();
		
		c_entity_motion_handler(const c_entity_motion_handler&) = delete;
		c_entity_motion_handler& operator=(const c_entity_motion_handler&) = delete;
	};
	template<class T>
	void c_entity_motion_handler::add(T& entity)
	{
		auto ptr = dynamic_cast<c_entity*>(&entity);
		m_vec_entities.push_back(ptr);
	}

}