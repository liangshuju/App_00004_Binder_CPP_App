
#define LOG_TAG "binder_cpp_test_client"

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>

#include "IHelloService.h"


using namespace android;

/*
 * ./test_client hello
 *
 * ./test_client hello <name>
 *
 *****/
 int main(int argc, char **argv)
 {
 	int cnt;

	if (argc < 2) {
		ALOGI("Usage : \n");
		ALOGI("%s <hello | goodbye> \n", argv[0]);
		ALOGI("%s <hello | goodbye> <name> \n", argv[0]);
		return -1;
	}

	/* getService */
	/* open driver, mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* get BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

	sp<IBinder> binder = sm->getService(String16("hello"));
	if (binder == 0) 
	{
		ALOGI("can not get hello service !\n");
		return -1;
	}

	/* service must is BpHelloService pointer */
	sp<IHelloService> service = interface_cast<IHelloService>(binder);

	/* call service function */
	if (argc < 3) 
	{
		service->sayhello();
		ALOGI(" client call sayhello.\n");
	}
	else
	{
		cnt = service->sayhello_to(argv[2]);
		ALOGI("client call sayhello_to , cnt = %d. \n", cnt);
	}

	return 0;
 }



