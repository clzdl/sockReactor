/*
 * sockBusinessObj.h
 *
 *  Created on: 2016年7月27日
 *      Author: clzdl
 */

#ifndef SOCKBUSINESSOBJ_H_
#define SOCKBUSINESSOBJ_H_

#include "libDefine.h"
#include "libAbstractHandler.h"



class CThreadObj : public Runnable
{
public:
    CThreadObj(IFactoryHandler *factory);

    CThreadObj(IFactoryHandler *factory , HTTPServerParams::Ptr param);
    void run();

    /*@action: 添加响应handler
     *
     */
    void AddEventHandler(StreamSocket &socket);

    /*@action: 删除响应handler
     *
     */
    void DeleteEventHandler(StreamSocket &socket);

    /*@action: 是否正在运行
     *
     */
    bool IsRunning();

    /*@action: 获取客户端数量
     *
     */
    int GetClientCount();

    /*@action: 获取http服务端参数设置
     *
     */
    HTTPServerParams* GetHttpServerParam();
private:
    CThreadObj(const CThreadObj &obj);
    CThreadObj& operator = (const CThreadObj &obj);

    SocketReactor m_sockReactor;

    std::map<int , IHandler*> m_mapClient;

    bool m_bRunning;

    IFactoryHandler *m_handerFactory;

    HTTPServerParams::Ptr m_httpServerParam;
};



#endif /* SOCKBUSINESSOBJ_H_ */
