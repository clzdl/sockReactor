/*
 * sockDispatcherHandler.h
 *
 *  Created on: 2016年7月27日
 *      Author: clzdl
 */

#ifndef SOCKACCEPTOR_H_
#define SOCKACCEPTOR_H_

#include "libDefine.h"


class CAcceptor
{
public:
    CAcceptor(ServerSocket& socket, SocketReactor& reactor);
    ~CAcceptor();

    void onAccept(ReadableNotification* pNotification);

private:

    CAcceptor(const CAcceptor &acceptor);
    CAcceptor& operator = (const CAcceptor &acceptor);

    void Dispatcher(StreamSocket &socket);

    ServerSocket m_sockServer;
    SocketReactor *m_sockReator;
};




#endif /* SOCKACCEPTOR_H_ */
