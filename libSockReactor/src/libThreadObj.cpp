/*
 * sockBusinessObj.cpp
 *
 *  Created on: 2016年7月27日
 *      Author: clzdl
 */



#include "libThreadObj.h"
#include "libAbstractHttpHandler.h"
//////////////

CThreadObj::CThreadObj(IFactoryHandler *factory)
:m_handerFactory(factory),
 m_bRunning(false),
 m_httpServerParam(NULL)
{

}

CThreadObj::CThreadObj(IFactoryHandler *factory , HTTPServerParams::Ptr param)
:m_handerFactory(factory),
 m_bRunning(false),
 m_httpServerParam(param)
{

}
void CThreadObj::run()
{
    m_bRunning = true;

    m_sockReactor.run();

    m_bRunning = false;
}

void CThreadObj::AddEventHandler(StreamSocket &socket)
{

    IHandler *handler = m_handerFactory->CreateHandler();

    handler->SetSocket(socket);
    handler->SetReactor(m_sockReactor);
    handler->SetThreadObj(this);

    if(_HttpSocket == handler->GetType())
    {
        dynamic_cast<IHttpHandler*>(handler)->SetHttpServerParam(m_httpServerParam);
    }

    m_sockReactor.addEventHandler(socket, Poco::Observer<IHandler, ReadableNotification>(*handler, &IHandler::cbReadable));
    m_sockReactor.addEventHandler(socket, Poco::Observer<IHandler, WritableNotification>(*handler, &IHandler::cbWriteable));
    m_sockReactor.addEventHandler(socket, Poco::Observer<IHandler, TimeoutNotification>(*handler, &IHandler::cbTimeout));
    m_sockReactor.addEventHandler(socket, Poco::Observer<IHandler, ErrorNotification>(*handler, &IHandler::cbError));
    m_sockReactor.addEventHandler(socket, Poco::Observer<IHandler, ShutdownNotification>(*handler, &IHandler::cbShutdown));

    m_mapClient.insert(std::pair<int , IHandler*>(socket.impl()->sockfd() , handler));
}


void CThreadObj::DeleteEventHandler(StreamSocket &socket)
{
    std::map<int , IHandler*>::iterator it = m_mapClient.find(socket.impl()->sockfd());

    if(it != m_mapClient.end())
    {

        m_sockReactor.removeEventHandler(socket, Poco::Observer<IHandler, ReadableNotification>(*(it->second), &IHandler::cbReadable));
        m_sockReactor.removeEventHandler(socket, Poco::Observer<IHandler, WritableNotification>(*(it->second), &IHandler::cbWriteable));
        m_sockReactor.removeEventHandler(socket, Poco::Observer<IHandler, TimeoutNotification>(*(it->second), &IHandler::cbTimeout));
        m_sockReactor.removeEventHandler(socket, Poco::Observer<IHandler, ErrorNotification>(*(it->second), &IHandler::cbError));
        m_sockReactor.removeEventHandler(socket, Poco::Observer<IHandler, ShutdownNotification>(*(it->second), &IHandler::cbShutdown));


        m_mapClient.erase(socket.impl()->sockfd());
    }
}

CThreadObj::CThreadObj(const CThreadObj &obj)
{

}

CThreadObj& CThreadObj::operator = (const CThreadObj &obj)
{

}

bool CThreadObj::IsRunning()
{
    return m_bRunning;
}

int CThreadObj::GetClientCount()
{
    return m_mapClient.size();
}


HTTPServerParams* CThreadObj::GetHttpServerParam()
{
    return m_httpServerParam;
}



