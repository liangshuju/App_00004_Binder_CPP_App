
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


#include "IHelloService.h"
#include "IGoodbyeService.h"

using namespace android;

/* usage : test_server <file> */
int main(int argc, const char **argv)
{
	int fd = 0;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDWR);
		if (fd == -1)
		{
			ALOGE("main thread open file failed : %s!!\n", strerror(fd));
			return -1;
		}
		else
		{
			ALOGI("test_server main thread open file : fd = %d\n", fd);
		}
	}
	else
	{
		ALOGE("Usage : you must input <%s> <file>!!\n", argv[1]);
		return -1;
	}
	
	/* addService */
	/* while(1) { read data, parse data , call server function } */

	/* open driver mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* get BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

	sm->addService(String16("hello"), new BnHelloService(fd));
	sm->addService(String16("goodbye"), new BnGoodbyeService());

	/* while */
	ProcessState::self()->startThreadPool(); /* create sub thread */
	
	IPCThreadState::self()->joinThreadPool(); /* main thread */

	return 0;
}





