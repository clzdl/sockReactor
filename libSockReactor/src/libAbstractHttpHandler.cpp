/*
 * libAbstractHttpHandler.cpp
 *
 *  Created on: 2016年7月29日
 *      Author: clzdl
 */


#include "libAbstractHttpHandler.h"
#include "libThreadObj.h"

IHttpHandler::IHttpHandler(_HType type)
:IHandler(type),
 m_httpServerSession(NULL),
 m_httpServerParams(NULL)
{

}
IHttpHandler::~IHttpHandler()
{

}

void IHttpHandler::onRead()
{




    bool bKeepConnection = false;
    std::string server = m_httpServerParams->getSoftwareVersion();

    DEBUG("keep-live:%d \n" , m_httpServerParams->getKeepAlive());

    if(m_httpServerSession == NULL)
        m_httpServerSession = new HTTPServerSession(m_socket, m_httpServerParams);
    try
    {
        HTTPServerResponseImpl response(*m_httpServerSession);

        DEBUG("keep-live:%d \n" , m_httpServerParams->getKeepAlive());
        ///there are some question about m_httpServerParams, coredump ,

        HTTPServerRequestImpl request(response, *m_httpServerSession, m_httpServerParams);

        DEBUG("keep-live:%d \n" , m_httpServerParams->getKeepAlive());

        Poco::Timestamp now;
        response.setDate(now);
        response.setVersion(request.getVersion());
        response.setKeepAlive(m_httpServerParams->getKeepAlive() && request.getKeepAlive() && m_httpServerSession->canKeepAlive());

        if (!server.empty())
            response.set("Server", server);


        onRequst(request ,response);

        bKeepConnection = response.getKeepAlive();


    }
    catch(Poco::Exception& e)
    {
        DEBUG("Exception:%s \n" , e.displayText().c_str());
    }


    if(!bKeepConnection)
    {
        delete m_httpServerSession;
        m_httpServerSession = NULL;

        m_threadObj->DeleteEventHandler(m_socket);
    }

}

void IHttpHandler::onWrite()
{

}

void IHttpHandler::SetHttpServerParam(HTTPServerParams::Ptr  param)
{
    m_httpServerParams = param;
}
