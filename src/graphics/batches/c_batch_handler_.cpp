//#include "c_batch_handler_.h"
//
//namespace owd
//{
//	c_batch_handler_* c_batch_handler_::m_singleton = nullptr;
//	
//	c_batch_handler_* owd::c_batch_handler_::get_instance()
//	{
//		if (m_singleton == nullptr)
//		{
//			m_singleton = new c_batch_handler_();
//		}
//
//		return m_singleton;
//	}
//	void c_batch_handler_::terminate()
//	{
//		if (m_singleton == nullptr)
//		{
//
//		}
//		else
//		{
//			delete m_singleton;
//			m_singleton = nullptr;
//		}
//	}
//	//void c_batch_handler_::reset()
//	//{
//	//	terminate();
//	//	init();
//	//}
//    c_batch_handler_::c_batch_handler_()
//    {
//		//init();
//    }
//    c_batch_handler_::~c_batch_handler_()
//    {
//    }
//}
