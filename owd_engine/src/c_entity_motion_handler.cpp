#include "c_entity_motion_handler.h"

namespace owd
{
	c_entity_motion_handler* c_entity_motion_handler::m_singleton = nullptr;

	void c_entity_motion_handler::move_one_tick()
	{
		#pragma omp parallel for  num_threads(4)
		for (int32_t i = 0; i < m_vec_entities.size(); ++i)
		{
			if (m_vec_entities[i] == nullptr)
			{
			}
			else if (m_vec_entities[i]->is_deleted())
			{
			}
			else
			{
				float delta_x = m_tick_time * (m_vec_entities[i]->velocity().x + m_vec_entities[i]->acceleration().x * m_tick_time / 2.0f);
				float delta_y = m_tick_time * (m_vec_entities[i]->velocity().y + m_vec_entities[i]->acceleration().y * m_tick_time / 2.0f);
				if (delta_x != 0.0f || delta_y != 0.0f)
				{
					m_vec_entities[i]->move(delta_x, delta_y);
				}

				float d_v_x = m_vec_entities[i]->acceleration().x * m_tick_time;
				float d_v_y = m_vec_entities[i]->acceleration().y * m_tick_time;

				if (d_v_x != 0.0f || d_v_y != 0.0f)
				{
					m_vec_entities[i]->set_velocity
					(
						m_vec_entities[i]->velocity().x + d_v_x,
						m_vec_entities[i]->velocity().y + d_v_y
					);
				}
			}
		}


		/*for (auto iter = m_vec_entities.begin(); iter != m_vec_entities.end();)
		{
			auto& entity = *iter;
			
			if (entity == nullptr)
			{
				m_vec_entities.erase(iter++);
			}
			else if (entity->is_deleted())
			{
				m_vec_entities.erase(iter++);
			}
			else
			{
				float delta_x = m_tick_time * (entity->velocity().x + entity->acceleration().x * m_tick_time / 2.0f);
				float delta_y = m_tick_time * (entity->velocity().y + entity->acceleration().y * m_tick_time / 2.0f);
				entity->move(delta_x, delta_y);
				entity->set_velocity
				(
					entity->velocity().x + entity->acceleration().x * m_tick_time,
					entity->velocity().y + entity->acceleration().y * m_tick_time
				);
				++iter;
			}
		}*/
	}

	void c_entity_motion_handler::clear()
	{
		m_vec_entities.clear();
	}

	c_entity_motion_handler* owd::c_entity_motion_handler::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_entity_motion_handler();
		}

		return m_singleton;
	}
	
	void c_entity_motion_handler::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
    c_entity_motion_handler::c_entity_motion_handler()
    {
    }
    c_entity_motion_handler::~c_entity_motion_handler()
    {
    }
}
