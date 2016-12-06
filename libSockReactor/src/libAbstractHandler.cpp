/*
 * sockAbstractHandler.cpp
 *
 *  Created on: 2016年7月29日
 *      Author: clzdl
 */



#include "libAbstractHandler.h"
#include "libThreadObj.h"

IHandler::IHandler(_HType type)
:m_sockReactor(NULL),
 m_threadObj(NULL),
 m_type(type)
{

}
IHandler::~IHandler()
{

}


void IHandler::cbReadable(ReadableNotification* pNotification)
{
    char szBuffer[4096] = {0};
    int iRecvLen = 0;
    if( m_socket.impl()->available() >0  )
    {
        onRead();
    }
    else
    {
        DEBUG("client disconnect.");
        m_socket.close();
        m_threadObj->DeleteEventHandler(m_socket);

    }
}


void IHandler::cbWriteable(WritableNotification* pNotification)
{

}


void IHandler::cbTimeout(TimeoutNotification* pNf)
{

}


void IHandler::cbError(ErrorNotification* pNf)
{

}


void IHandler::cbShutdown(ShutdownNotification* pNf)
{

}


void IHandler::SetSocket(StreamSocket &socket)
{
    m_socket = socket;
}

void IHandler::SetReactor(SocketReactor &reactor)
{
    m_sockReactor = &reactor;
}

void IHandler::SetThreadObj(CThreadObj *obj)
{
    m_threadObj = obj;
}




//////


IFactoryHandler::IFactoryHandler()
{

}

IFactoryHandler::~IFactoryHandler()
{

}

IHandler* IFactoryHandler::CreateHandler()
{
    return NULL;
}
