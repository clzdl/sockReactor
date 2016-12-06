/*
 * sockFramework.h
 *
 *  Created on: 2016年7月27日
 *      Author: clzdl
 */

#ifndef SOCKFRAMEWORK_H_
#define SOCKFRAMEWORK_H_

#include "libDefine.h"

#include "libAcceptor.h"
#include "libAbstractHandler.h"

/*
 *
 * */



class CBusinessObj;
class CFramework
{
public:

    /*@action:创建framework实例
     *
     */
    static CFramework* CreateServer(std::string strDomain , unsigned int port , unsigned int threadCnt , IFactoryHandler *factory);

    /*@action:创建framework的http实例
     *
     */
    static CFramework* CreateHttpServer(std::string strDomain , unsigned int port , unsigned int threadCnt , IFactoryHandler *factory ,HTTPServerParams::Ptr param);


    /*@action: 获取framework实例
     *
     */
    static CFramework* Instance();


    /*@action: 监听线程
     *
     */
    static void ThreadFun(void *param);


    /*@action: 对新接入的客户端进行分发
     *
     */
    void Dispatch(StreamSocket &socket);

    /*@action: 框架开始运行
     *
     */
    void Run();

    /*@action: 停止框架运行
     *
     */
    void Stop();

private:

    CFramework(std::string strDomain ,unsigned int port , unsigned int threadCnt, IFactoryHandler *factory );
    CFramework(std::string strDomain ,unsigned int port , unsigned int threadCnt, IFactoryHandler *factory ,HTTPServerParams::Ptr param);
    CFramework(const CFramework &framework);
    CFramework& operator =(const CFramework &framework);




    static CFramework *m_objInstance;

    SocketReactor m_sockReactor;

    std::string m_strDomain;
    unsigned int m_uiPort;
    unsigned int m_uiThreadCnt;

    IFactoryHandler *m_handlerFactory;

    ////must use Poco::AutoPtr to contain HTTPServerParams,  lifetime same to the framework
    HTTPServerParams::Ptr m_httpParam;
    std::vector<CThreadObj*> m_vecContainer;

    ThreadPool *m_tpPool;

    Event m_etWaitStop;

    Thread m_thread;

};


#endif /* SOCKFRAMEWORK_H_ */
