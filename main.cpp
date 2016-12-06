/*
 * main.cpp
 *
 *  Created on: 2016年7月28日
 *      Author: clzdl
 */



#include "libFramework.h"
#include "sockBusinessHandler.h"


int main(int argc , char* argv[])
{

    //CFramework::CreateServer("192.168.131.12" , 4444 ,2 , new CFactoryHandler());

    HTTPServerParams* pParams = new HTTPServerParams;
    pParams->setKeepAlive(true);
    CFramework::CreateHttpServer("192.168.131.12" , 4444 ,2 , new CFactoryHttpHandler() , pParams);


    CFramework::Instance()->Run();

    return 0;
}
