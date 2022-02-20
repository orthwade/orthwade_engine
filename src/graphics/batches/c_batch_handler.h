#pragma once
#include "c_graphic_batch.h"

namespace owd
{
	struct s_level
	{
		//uint16_t level{};
		std::vector<c_graphic_batch> batches{};
	};
	class c_batch_handler
	{
	public:
		s_level& get_level(uint16_t level);

	private:
		std::vector<s_level> m_levels{};
	
	};
}