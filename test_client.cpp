
#define LOG_TAG "binder_cpp_test_client"

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <unistd.h>
#include <sys/types.h>


#include "IHelloService.h"
#include "IGoodbyeService.h"


using namespace android;

/*
 * ./test_client hello/goodbye
 *
 * ./test_client hello/goodbye <name>
 *
 * ./test_client hello <readfile>
 ****/

 void do_process(int fd)
 {
	 int len = 0;
	 int cnt = 0;
	 char buf[512] = {0};
 
	 while(1)
	 {
		 /* send data to test_server */
		 len = sprintf(buf, "Hello, test_server process, cnt = %d", cnt ++);
		 write(fd, buf, len);
 
		 /* read data form test_server */
		 len = read(fd, buf, 512);
		 buf[len] = '\0';
		 ALOGI("test_client read data = %s.\n", buf);
 
		 sleep(6);// 避免打印信息太多
	 }
 }


 int main(int argc, char **argv)
 {
 	int cnt;

	if (argc < 2) {
		ALOGI("Usage : \n");
		ALOGI("%s <hello | goodbye> \n", argv[0]);
		ALOGI("%s <hello | goodbye> <name> \n", argv[0]);
		ALOGI("%s <readfile> \n", argv[0]);
		return -1;
	}

	/* getService */
	/* open driver, mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* get BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();


	if (!strcmp(argv[1], "hello")) 
	{			
		sp<IBinder> binderHello = sm->getService(String16("hello"));
		if (binderHello == 0) 
		{
			ALOGI("can not get hello service !\n");
			return -1;
		}

		/* service must is BpHelloService pointer */
		sp<IHelloService> serviceHello = interface_cast<IHelloService>(binderHello);
		
		/* call service function */
		if (argc < 3) 
		{
			serviceHello->sayhello();
			ALOGI("client call sayhello.\n");
		}
		else
		{
			cnt = serviceHello->sayhello_to(argv[2]);
			ALOGI("client call sayhello_to , cnt = %d. \n", cnt);
		}
		
	}
	else if (!strcmp(argv[1], "goodbye")) 
	{
		sp<IBinder> binderGoodbye = sm->getService(String16("goodbye"));
		if (binderGoodbye == 0) 
		{
			ALOGI("can not get goodbye service !\n");
			return -1;
		}

		sp<IGoodbyeService> serviceGoodbye = interface_cast<IGoodbyeService>(binderGoodbye);
		if (argc == 2) 
		{
			serviceGoodbye->saygoodbye();
			ALOGI("client call say goodbye service .");
		}		
		else if (argc == 3)
		{
			cnt = serviceGoodbye->saygoodbye_to(argv[2]);
			ALOGI("client call say goodbye to service : cnt = %d.", cnt);
		}
	}
	else if (!strcmp(argv[1], "readfile"))
	{
		/* call service function */		
		sp<IBinder> binderHello = sm->getService(String16("hello"));
		if (binderHello == 0) 
		{
			ALOGI("can not get hello service !\n");
			return -1;
		}

		/* service must is BpHelloService pointer */
		sp<IHelloService> serviceHello = interface_cast<IHelloService>(binderHello);

		ALOGI("client get fd .\n");

		int fd = serviceHello->get_fd();
		ALOGI("client get fd = %d.\n", fd);

		do_process(fd);

	}
	else
	{
		ALOGI("client get service failed!");
	}

	return 0;
 }



