#Makefile#

CC=g++ -g -lm -lpthread -lc -lnsl -lrt -ldl -fPIC

#模块名称(必填)
MODULE = libSockReactor.so

#目标文件集合(必填)
OBJS =  libAcceptor.cpp\
		libThreadObj.cpp\
		libAbstractHandler.cpp\
		libAbstractHttpHandler.cpp\
		libFramework.cpp
         

#链接库集合
LIB = -L${HOME}/lib -lPocoNet -lPocoFoundation
 
        

#头文件路径
INC =  -I../include/. \
       -I${HOME}/frames/poco-1.4.6p4/Foundation/include \
       -I${HOME}/frames/poco-1.4.6p4/Net/include
      

#调试
DEBUG = -D_DEBUG 

#编译参数 C++11版本参数 -std=c++0x
CFLAGS = 

#链接参数
LFLAGS = 

OBJS:=${OBJS:%.cpp=%.o}

.SUFFIXES:.cpp .o
.cpp.o:
	@echo "-----Compile $<"
	$(CC) $(CFLAGS) $(INC) ${DEBUG}-o $@ -c $<
	@echo "-----Compile $< Done"
	@echo ""
        
all: MODULE

MODULE:${OBJS}
	${CC} -shared -o $(MODULE)  $(OBJS)
	
	
clean:
	rm -f ${OBJS}	


install:
	cp ${MODULE} ../lib/.
