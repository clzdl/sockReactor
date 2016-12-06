/*
 * sockAcceptor.cpp
 *
 *  Created on: 2016年7月27日
 *      Author: clzdl
 */


#include "libAcceptor.h"
#include "libFramework.h"


CAcceptor::CAcceptor(ServerSocket& socket, SocketReactor& reactor)
:m_sockServer(socket),
 m_sockReator(&reactor)
{
    m_sockReator->addEventHandler(m_sockServer, Poco::Observer<CAcceptor, ReadableNotification>(*this, &CAcceptor::onAccept));
}

CAcceptor::~CAcceptor()
{
    if (m_sockReator)
    {
        m_sockReator->removeEventHandler(m_sockServer, Poco::Observer<CAcceptor, ReadableNotification>(*this, &CAcceptor::onAccept));
    }
}


void CAcceptor::onAccept(ReadableNotification* pNotification)
{
    pNotification->release();
    StreamSocket sock = m_sockServer.acceptConnection();
    DEBUG("client:%s \n" , sock.address().toString().c_str());
    Dispatcher(sock);
}


void CAcceptor::Dispatcher(StreamSocket &socket)
{
    CFramework::Instance()->Dispatch(socket);
}
