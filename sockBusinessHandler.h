/*
 * sockBusinessHandler.h
 *
 *  Created on: 2016年7月29日
 *      Author: clzdl
 */

#ifndef SOCKBUSINESSHANDLER_H_
#define SOCKBUSINESSHANDLER_H_

#include "libAbstractHandler.h"
#include "libAbstractHttpHandler.h"


class CHandler: public IHandler
{
public:
    CHandler(_HType type);

    ~CHandler();

    void onRead();


    void onWrite();


};

class CHttpHandler: public IHttpHandler
{
public:
    CHttpHandler(_HType type);

    ~CHttpHandler();

    void onRequst(HTTPServerRequestImpl &request , HTTPServerResponseImpl &response);
};





class CFactoryHandler : public IFactoryHandler
{
public:
    CFactoryHandler()
    {

    }

    ~CFactoryHandler()
    {

    }

    IHandler* CreateHandler()
    {
        return new CHandler(_NorSocket);
    }

};


class CFactoryHttpHandler : public IFactoryHandler
{
public:
    CFactoryHttpHandler()
    {

    }

    ~CFactoryHttpHandler()
    {

    }

    IHandler* CreateHandler()
    {
        return new CHttpHandler(_HttpSocket);
    }

};

#endif /* SOCKBUSINESSHANDLER_H_ */
