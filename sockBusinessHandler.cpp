/*
 * sockBusinessHandler.cpp
 *
 *  Created on: 2016年7月29日
 *      Author: clzdl
 */


#include "sockBusinessHandler.h"


CHandler::CHandler(_HType type)
:IHandler(type)
{
}

CHandler::~CHandler()
{

}

void CHandler::onRead()
{
    DEBUG("=====onRead=====\n");

    char szBuffer[4096] = {0};

    int iSize = m_socket.receiveBytes(szBuffer , sizeof(4096));

    m_socket.sendBytes(szBuffer ,iSize );


}


void CHandler::onWrite()
{

}



/////////////
CHttpHandler::CHttpHandler(_HType type)
:IHttpHandler(type)
{

}

CHttpHandler::~CHttpHandler()
{

}

void CHttpHandler::onRequst(HTTPServerRequestImpl &request , HTTPServerResponseImpl &response)
{
    DEBUG("========== onRequst ===========\n");

    std::istream &istr = request.stream();

    std::ostringstream ss;
    StreamCopier::copyStream(istr, ss);

    response.send()<<ss.str();

}


