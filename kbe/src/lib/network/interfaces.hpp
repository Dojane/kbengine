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

#ifndef __NETWORK_INTERFACES__
#define __NETWORK_INTERFACES__

namespace KBEngine { 
namespace Mercury
{
class Channel;

/** 此类接口用于接收普通的Mercury输入消息
*/
class InputNotificationHandler
{
public:
	virtual ~InputNotificationHandler() {};
	virtual int handleInputNotification(int fd) = 0;
};

/** 此类接口用于接收普通的Mercury输出消息
*/
class OutputNotificationHandler
{
public:
	virtual ~OutputNotificationHandler() {};
	virtual int handleOutputNotification(int fd) = 0;
};

/** 此类接口用于接收一个网络通道超时消息
*/
class ChannelTimeOutHandler
{
public:
	virtual void onTimeOut(Channel * pChannel) = 0;
};

}
}
#endif // __NETWORK_INTERFACES__