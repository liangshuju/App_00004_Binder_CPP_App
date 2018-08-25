

/*
 * reference : frameworks\av\media\libmedia\IMediaPlayerService.cpp
*/

#define LOG_TAG "binder_cpp_BnGoodbyeService"

#include "IGoodbyeService.h"

namespace android {

status_t BnGoodbyeService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{

	/* parse data, call sayhello/sayhello_to */
	switch(code) 
	{

		case GOODBYE_SVC_CMD_SAY_GOODBYE:
		{
			saygoodbye();
			reply->writeInt32(0);  /* no exception */
			
			return NO_ERROR;
		}
		break;

		case GOODBYE_SVC_CMD_SAY_GOODBYE_TO:
		{
			/* Get Data form para */
			int32_t policy = data.readInt32();

			String16 goodbyeServiceDescriptorString16 = data.readString16(); /* IGoodbyeService */
			String8 name8Goodbye(goodbyeServiceDescriptorString16);
			ALOGI("onTransact : service = %s.\n", name8Goodbye.string());
			
			String16 name16 = data.readString16();
			String8 name8(name16);

			int cnt = saygoodbye_to(name8.string());

			/* set return value write reply return */
			reply->writeInt32(0);  /* no exception */
			reply->writeInt32(cnt);

			return NO_ERROR;
		}
		break;

		default:
			return BBinder::onTransact(code, data, reply, flags);
	}
}

void BnGoodbyeService::saygoodbye(void)
{
	static int cnt = 0;
	ALOGI("say goodbye : %d \n", ++ cnt);
}

int BnGoodbyeService::saygoodbye_to(const char * name)
{
	static int cnt = 0;
	ALOGI("say goodbye to %s : %d \n", name, ++ cnt);
	return cnt;
}

}

