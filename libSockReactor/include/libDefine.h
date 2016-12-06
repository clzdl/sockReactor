/*
 * sockDefine.h
 *
 *  Created on: 2016年7月27日
 *      Author: clzdl
 */

#ifndef SOCKDEFINE_H_
#define SOCKDEFINE_H_



#include <sstream>
#include <map>
#include <vector>

#include <iostream>
#include <string>

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketConnector.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Observer.h"

#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerSession.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerRequestImpl.h"
#include "Poco/Net/HTTPServerResponseImpl.h"
#include "Poco/Net/NetException.h"

#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadTarget.h"
#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "Poco/AutoPtr.h"
#include "Poco/StreamCopier.h"





using Poco::Net::SocketReactor;
using Poco::Net::SocketConnector;
using Poco::Net::StreamSocket;
using Poco::Net::ServerSocket;
using Poco::Net::SocketAddress;
using Poco::Net::SocketNotification;
using Poco::Net::ReadableNotification;
using Poco::Net::WritableNotification;
using Poco::Net::ErrorNotification;
using Poco::Net::TimeoutNotification;
using Poco::Net::ShutdownNotification;
using Poco::Observer;


using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServerSession;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerRequestImpl;
using Poco::Net::HTTPServerResponseImpl;
using Poco::Net::NetException;


using Poco::Thread;
using Poco::ThreadPool;
using Poco::Runnable;
using Poco::ThreadTarget;
using Poco::FastMutex;
using Poco::ScopedLock;
using Poco::Mutex;
using Poco::Exception;
using Poco::Event;
using Poco::AutoPtr;

using Poco::StreamCopier;


#ifdef _DEBUG
#define DEBUG(FMT,...)      printf("[%s,%d]"FMT ,__FILE__ ,__LINE__, ##__VA_ARGS__)
#else
#define DEBUG(FMT,...)
#endif


#endif /* SOCKDEFINE_H_ */
