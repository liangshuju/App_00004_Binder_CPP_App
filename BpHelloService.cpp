/*
 * reference : frameworks\av\media\libmedia\IMediaPlayerService.cpp
 **/
 
#define LOG_TAG "binder_cpp_BpHelloService"


#include "IHelloService.h"
#include <utils/Log.h>

namespace android {

class BpHelloService : public BpInterface<IHelloService>
{
public:
	BpHelloService(const sp<IBinder>& impl) : BpInterface<IHelloService>(impl)
	{

	}

	void sayhello(void)
	{
		/* construction data and send data */
		Parcel data, reply;
		data.writeInt32(0);
		data.writeString16(String16(HELLO_SERVER_DESCRIPTOR));

		remote()->transact(HELLO_SVC_CMD_SAY_HELLO, data, &reply);
	}

	int sayhello_to(const char *name)
	{
		/* construction data and send to data */
		Parcel data, reply;
		int exception;

		data.writeInt32(0);
		data.writeString16(String16(HELLO_SERVER_DESCRIPTOR));
		data.writeString16(String16(name));

		remote()->transact(HELLO_SVC_CMD_SAY_HELLO_TO, data, &reply);
	
		exception = reply.readInt32();
		if (exception)
		{
			ALOGE("sayhello_to exception.");
			return -1;
		}
		else 
		{
			return reply.readInt32();
		}
	
	}
	
};

IMPLEMENT_META_INTERFACE(HelloService, "android.test.IHelloService");

}





