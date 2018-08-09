
/*
 * reference : frameworks\av\media\libmedia\IMediaPlayerService.cpp
 **/

 #include "IHelloService.h"

class BpHelloService: public BpInterface<IHelloService>
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

		remote()->transact(HELLO_SVC_CMD_SAY_HELLO, data, &reply);
	}

	int sayhello_to(const char *name)
	{
		/* construction data and send to data */
		Parcel data, reply;

		data.writeInt32(0);
		data.writeString16(String16(name));

		remote()->transact(HELLO_SVC_CMD_SAY_HELLO_TO, data, &reply);

		return reply.readInt32();
	}
	
};

IMPLEMENT_META_INTERFACE(HelloService, "android.media.IHelloService");








