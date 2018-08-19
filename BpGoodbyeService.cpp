/*
 * reference : frameworks\av\media\libmedia\IMediaPlayerService.cpp
 **/

#include "IGoodbyeService.h"

namespace android {

class BpGoodbyeService : public BpInterface<IGoodbyeService>
{
public:
	BpGoodbyeService(const sp<IBinder>& impl) : BpInterface<IGoodbyeService>(impl)
	{

	}

	void saygoodbye(void)
	{
		/* construction data and send data */
		Parcel data, reply;
		data.writeInt32(0);

		remote()->transact(GOODBYE_SVC_CMD_SAY_GOODBYE, data, &reply);
	}

	int saygoodbye_to(const char *name)
	{
		/* construction data and send to data */
		Parcel data, reply;

		data.writeInt32(0);
		data.writeString16(String16(name));

		remote()->transact(GOODBYE_SVC_CMD_SAY_GOODBYE_TO, data, &reply);

		return reply.readInt32();
	}
	
};

IMPLEMENT_META_INTERFACE(GoodbyeService, "android.test.IGoodbyeService");

}





