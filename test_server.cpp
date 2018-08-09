
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
#include <uitls/Log.h>

using namespace android;

void main(void)
{

	/* addService */
	/* while(1) { read data, parse data , call server function } */

	/* open driver mmap */
	sp<ProcessState> proc(ProcessState::self());

	/* get BpServiceManager */
	sp<IServiceManager> sm = defaultServiceManager();

	sm->addService(String16("hello"), new BnHelloService());

	/* while */
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
}





