
/*
 * reference: frameworks\av\media\mediaserver\Main_mediaservice.cpp
 *
 *
 ****/

#define LOG_TAG "binder_cpp_test_server"

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <string.h>
#include <errno.h>


#include "IHelloService.h"
#include "IGoodbyeService.h"

#define SOCKET_BUFFER_SIZE (32768U)

using namespace android;

/* reference:
 *
 * http://blog.csdn.net/linan_nwu/article/details/8222349 
 *
 */

class MyThread: public Thread {
private:
	int fd;

public:
	MyThread();
	MyThread(int fd)
	{
		this->fd = fd;
	}

	// return true, loop call this funciton; return false, this function only call one time 
	bool threadLoop()
	{
		char buf[512] = {0};
		int cnt = 0;
		int len = 0;

		while(1)
		{
			/* read data from test_client send it data */	
			len = read(fd, buf, 512);
			buf[len] = '\0';
			ALOGI("test_server : read data = %s.\n", buf);

			/* server send data to client */
			len = sprintf(buf, "Hello, test_client, cnt = %d", cnt ++);
			write(fd, buf, len);
		}

		return true;
	}

};


int main(void)
{
	int sockets[2];
	int buffer_size = SOCKET_BUFFER_SIZE;
	
	socketpair(AF_UNIX, SOCK_SEQPACKET, 0, sockets); // af_unix sock_seqpacket
	setsockopt(sockets[0], SOL_SOCKET, SO_SNDBUF, &buffer_size, sizeof(buffer_size));
	setsockopt(sockets[0], SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size));
	setsockopt(sockets[1], SOL_SOCKET, SO_SNDBUF, &buffer_size, sizeof(buffer_size));
	setsockopt(sockets[1], SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size));

	/* create thrad, use it and test_client by socketpair communication */
	//MyThread th = new MyThread(sockets[0]); // error
	sp<MyThread> th = new MyThread(sockets[0]); // ok
	th->run();
	
	/* addService */
	/* while(1) { read data, parse data , call server function } */

	/* open driver mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* get BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

	sm->addService(String16("hello"), new BnHelloService(sockets[1]));
	sm->addService(String16("goodbye"), new BnGoodbyeService());

	/* while */
	ProcessState::self()->startThreadPool(); /* create sub thread */
	
	IPCThreadState::self()->joinThreadPool(); /* main thread */

	return 0;
}





