/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#if defined(DEFINE_IN_INTERFACE)
	#undef __CELLAPP_INTERFACE_H__
#endif


#ifndef __CELLAPP_INTERFACE_H__
#define __CELLAPP_INTERFACE_H__

// common include	
#if defined(CELLAPP)
#include "entity.hpp"
#include "cellapp.hpp"
#endif
#include "network/interface_defs.hpp"
//#define NDEBUG
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{
/**
	Entity消息宏，  参数为流， 需要自己解开
*/
#if defined(NETWORK_INTERFACE_DECLARE_BEGIN)
	#undef ENTITY_MESSAGE_HANDLER_STREAM
#endif

#if defined(DEFINE_IN_INTERFACE)
#if defined(CELLAPP)
#define ENTITY_MESSAGE_HANDLER_STREAM(NAME)										\
	void NAME##EntityMessagehandler_stream::handle(KBEngine::MemoryStream& s)	\
	{																			\
			ENTITY_ID eid;														\
			s >> eid;															\
			KBEngine::Entity* e =												\
					KBEngine::CellApp::getSingleton().findEntity(eid);			\
			e->NAME(s);															\
	}																			\

#else
#define ENTITY_MESSAGE_HANDLER_STREAM(NAME)										\
	void NAME##EntityMessagehandler_stream::handle(KBEngine::MemoryStream& s)	\
	{																			\
	}																			\
		
#endif
#else
#define ENTITY_MESSAGE_HANDLER_STREAM(NAME)										\
	class NAME##EntityMessagehandler_stream : public Mercury::MessageHandler	\
	{																			\
	public:																		\
		virtual void handle(KBEngine::MemoryStream& s);							\
	};																			\

#endif

#define ENTITY_MESSAGE_DECLARE_STREAM(NAME, MSG_LENGTH)							\
	ENTITY_MESSAGE_HANDLER_STREAM(NAME)											\
	NETWORK_MESSAGE_DECLARE_STREAM(Entity, NAME,								\
				NAME##EntityMessagehandler_stream, MSG_LENGTH)					\
																				\

/**
	Entity消息宏，  只有一个参数的消息
*/
#if defined(NETWORK_INTERFACE_DECLARE_BEGIN)
	#undef ENTITY_MESSAGE_HANDLER_ARGS1
#endif

#if defined(DEFINE_IN_INTERFACE)
#if defined(CELLAPP)
#define ENTITY_MESSAGE_HANDLER_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)				\
	void NAME##EntityMessagehandler1::handle(KBEngine::MemoryStream& s)			\
	{																			\
			ENTITY_ID eid;														\
			s >> eid;															\
			KBEngine::Entity* e =												\
					KBEngine::CellApp::getSingleton().findEntity(eid);			\
			ARG_TYPE1 ARG_NAME1;												\
			s >> ARG_NAME1;														\
			e->NAME(ARG_NAME1);													\
	}																			\

#else
#define ENTITY_MESSAGE_HANDLER_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)				\
	void NAME##EntityMessagehandler1::handle(KBEngine::MemoryStream& s)			\
	{																			\
	}																			\
		
#endif
#else
#define ENTITY_MESSAGE_HANDLER_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)				\
	class NAME##EntityMessagehandler1 : public Mercury::MessageHandler			\
	{																			\
	public:																		\
		virtual void handle(KBEngine::MemoryStream& s);							\
	};																			\

#endif

#define ENTITY_MESSAGE_DECLARE_ARGS1(NAME, MSG_LENGTH, ARG_TYPE1, ARG_NAME1)	\
	ENTITY_MESSAGE_HANDLER_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)					\
	NETWORK_MESSAGE_DECLARE_ARGS1(Entity, NAME,									\
				NAME##EntityMessagehandler1, MSG_LENGTH, ARG_TYPE1, ARG_NAME1)	\
																				\



/**
	cellapp所有消息接口在此定义
*/
NETWORK_INTERFACE_DECLARE_BEGIN(CellAppInterface)
	
	ENTITY_MESSAGE_DECLARE_ARGS1(test, MERCURY_VARIABLE_MESSAGE,
								std::string, name
	)
	
	/**
		远程呼叫entity方法
	*/
	ENTITY_MESSAGE_DECLARE_STREAM(onRemoteMethodCall, MERCURY_FIXED_MESSAGE)
	
NETWORK_INTERFACE_DECLARE_END()

#ifdef DEFINE_IN_INTERFACE
	#undef DEFINE_IN_INTERFACE
#endif

}
#endif
