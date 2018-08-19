
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

#include "IHelloService.h"
#include "IGoodbyeService.h"

using namespace android;

int main(void)
{
	/* addService */
	/* while(1) { read data, parse data , call server function } */

	/* open driver mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* get BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

	sm->addService(String16("hello"), new BnHelloService());
	sm->addService(String16("goodbye"), new BnGoodbyeService());

	/* while */
	ProcessState::self()->startThreadPool(); /* create sub thread */
	
	IPCThreadState::self()->joinThreadPool(); /* main thread */

	return 0;
}





