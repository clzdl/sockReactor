/*
 * libAbstractHttpHandler.h
 *
 *  Created on: 2016年7月29日
 *      Author: clzdl
 */

#ifndef LIBSOCKREACTOR_INCLUDE_LIBABSTRACTHTTPHANDLER_H_
#define LIBSOCKREACTOR_INCLUDE_LIBABSTRACTHTTPHANDLER_H_


#include "libDefine.h"
#include "libAbstractHandler.h"

class IHttpHandler: public IHandler
{
public:
    IHttpHandler(_HType type);
    virtual ~IHttpHandler();

    /*@action: 可读时调用的回调
     *
     */
    void onRead();


    void onWrite();


    /*@action: 实现具体的业务
     *
     */
    virtual void onRequst(HTTPServerRequestImpl &request , HTTPServerResponseImpl &response) = 0;

    void SetHttpServerParam(HTTPServerParams::Ptr param);

protected:

    HTTPServerSession *m_httpServerSession;

    HTTPServerParams::Ptr m_httpServerParams;
};





#endif /* LIBSOCKREACTOR_INCLUDE_LIBABSTRACTHTTPHANDLER_H_ */
