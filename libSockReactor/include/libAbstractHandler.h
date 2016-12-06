/*
 * sockAbstractHandler.h
 *
 *  Created on: 2016年7月29日
 *      Author: clzdl
 */

#ifndef SOCKABSTRACTHANDLER_H_
#define SOCKABSTRACTHANDLER_H_

#include "libDefine.h"

class CThreadObj;

typedef enum{
    _NorSocket,
    _HttpSocket,
} _HType;

class IHandler
{
public:
    IHandler(_HType type);
    virtual ~IHandler();

    /*@action: 可读时调用的回调
     *
     */
    virtual void cbReadable(ReadableNotification* pNotification);


    /*@action: 实现具体的业务
     *
     */
    virtual void onRead() = 0;

    /*@action: 可写时调用的回调
     *
     */
    virtual void cbWriteable(WritableNotification* pNotification);

    /*@action: 实现具体的业务
     *
     */
    virtual void onWrite() = 0;

    /*@action: 超时时调用的回调
     *
     */
    virtual void cbTimeout(TimeoutNotification* pNf);

    /*@action: 错误时的回调
     *
     */
    virtual void cbError(ErrorNotification* pNf);


    /*@action: 本地关闭操作时的回调
     *
     */
    virtual void cbShutdown(ShutdownNotification* pNf);


    void SetSocket(StreamSocket &socket);

    void SetReactor(SocketReactor &reactor);

    void SetThreadObj(CThreadObj *obj);

    _HType GetType() { return m_type;}
protected:

    StreamSocket m_socket;
    SocketReactor *m_sockReactor;

    CThreadObj *m_threadObj;

    _HType m_type;
};






class IFactoryHandler
{
public:
    IFactoryHandler();

    virtual ~IFactoryHandler();

    virtual IHandler* CreateHandler() = 0;

};

#endif /* SOCKABSTRACTHANDLER_H_ */
