/*
 * sockFramework.cpp
 *
 *  Created on: 2016年7月27日
 *      Author: clzdl
 */



#include "libFramework.h"
#include "libThreadObj.h"

CFramework *CFramework::m_objInstance = NULL;

CFramework* CFramework::CreateServer(std::string strDomain , unsigned int port , unsigned int threadCnt, IFactoryHandler *factory)
{
    if(m_objInstance == NULL)
    {
        m_objInstance = new CFramework(strDomain , port , threadCnt,factory);
    }
    return m_objInstance;
}

CFramework* CFramework::CreateHttpServer(std::string strDomain , unsigned int port , unsigned int threadCnt , IFactoryHandler *factory ,HTTPServerParams::Ptr param)
{
    if(m_objInstance == NULL)
    {
        m_objInstance = new CFramework(strDomain , port , threadCnt,factory,param);
    }
    return m_objInstance;
}

CFramework* CFramework::Instance()
{
    assert(NULL != m_objInstance);
    return m_objInstance;
}


CFramework::CFramework(std::string strDomain,unsigned int port , unsigned int threadCnt, IFactoryHandler *factory)
:m_strDomain(strDomain),
 m_uiPort(port),
 m_uiThreadCnt(threadCnt),
 m_tpPool(new ThreadPool(1, threadCnt ,  60*60)),
 m_handlerFactory(factory),
 m_httpParam(NULL)
{
    for(unsigned int i = 0 ; i < threadCnt ; ++i)
    {
        m_vecContainer.push_back(new CThreadObj(factory));
    }
}


CFramework::CFramework(std::string strDomain,unsigned int port , unsigned int threadCnt, IFactoryHandler *factory,HTTPServerParams::Ptr param)
:m_strDomain(strDomain),
 m_uiPort(port),
 m_uiThreadCnt(threadCnt),
 m_tpPool(new ThreadPool(1, threadCnt ,  60*60)),
 m_handlerFactory(factory),
 m_httpParam(param)
{
    for(unsigned int i = 0 ; i < threadCnt ; ++i)
    {
        m_vecContainer.push_back(new CThreadObj(factory , param));
    }
}
void CFramework::Dispatch(StreamSocket &socket)
{
    unsigned int pos = socket.impl()->sockfd()%m_uiThreadCnt;
    m_vecContainer[pos]->AddEventHandler(socket);

    DEBUG("position:%d , size: %d \n" , pos , m_vecContainer[pos]->GetClientCount());

    if(!m_vecContainer[pos]->IsRunning())
        m_tpPool->start(*(m_vecContainer[pos]));
}

void CFramework::Run()
{
    m_etWaitStop.reset();

    m_thread.start(CFramework::ThreadFun , this);

    m_etWaitStop.wait();

    m_sockReactor.stop();
}

void CFramework::Stop()
{
    m_etWaitStop.set();
}

void CFramework::ThreadFun(void *param)
{
    CFramework *framework = (CFramework*) param;

    SocketAddress ssa(framework->m_strDomain ,framework->m_uiPort);

    ServerSocket ss(ssa);

    CAcceptor acceptor(ss , framework->m_sockReactor);


    framework->m_sockReactor.run();

}
