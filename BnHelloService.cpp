

/*
 * reference : frameworks\av\media\libmedia\IMediaPlayerService.cpp
*/

#define LOG_TAG "binder_cpp_BnHelloService"

#include "IHelloService.h"

namespace android {

BnHelloService::BnHelloService()
{

}

BnHelloService::BnHelloService(int fd)
{
	this->fd = fd;
}

status_t BnHelloService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{

	/* parse data, call sayhello/sayhello_to */
	switch(code) 
	{

		case HELLO_SVC_CMD_SAY_HELLO:
		{
			sayhello();
			reply->writeInt32(0);  /* no exception */
			return NO_ERROR;
		}
		break;

		case HELLO_SVC_CMD_SAY_HELLO_TO:
		{
			/* Get Data form para */
			int32_t policy = data.readInt32();
			String16 helloServiceDescriptorString16 = data.readString16(); /* IHelloService */
			String8 name8Hello(helloServiceDescriptorString16);
			ALOGI("onTransact : service = %s.\n", name8Hello.string());
			
			String16 name16 = data.readString16();
			String8 name8(name16);

			int cnt = sayhello_to(name8.string());

			/* set return value write reply return */
			reply->writeInt32(0);  /* no exception */
			reply->writeInt32(cnt);

			return NO_ERROR;
		}
		break;

		case HELLO_SVC_CMD_GET_FD:
		{
			int fd = this->get_fd();
			reply->writeInt32(0); /* no execption */

			/*
			 * reference: 
			 * frameworks\base\core\jni\android_view_InputChannel.cpp
			 * android_view_InputChannel_nativeWriteParcel
			 ***/
			//reply->writeFileDescriptor(fd, 1); //  ~Pracel() ; close fd; 
			reply->writeDupFileDescriptor(fd);
			ALOGI(" server get_fd : fd = %d.\n", fd);
			return NO_ERROR;
		}
		break;

		default:
			return BBinder::onTransact(code, data, reply, flags);
	}
}

void BnHelloService::sayhello(void)
{
	static int cnt = 0;
	ALOGI("say hello : %d \n", ++ cnt);
}

int BnHelloService::sayhello_to(const char * name)
{
	static int cnt = 0;
	ALOGI("say hello to %s : %d \n", name, ++ cnt);
	return cnt;
}

int BnHelloService::get_fd(void)
{
	return fd;
}

}

