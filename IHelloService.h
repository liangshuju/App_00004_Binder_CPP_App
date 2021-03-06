

/*
 * reference : frameworks/av/inclue/media/IMediaPlayerService.h
*/

#ifndef ANDROID_IHELLOSERVICE_H
#define ANDROID_IHELLOSERVICE_H

#include <utils/Errors.h> // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>

#include <binder/IInterface.h>
#include <binder/Parcel.h>

//#define HELLO_SVC_CMD_SAY_HELLO    0
//#define HELLO_SVC_CMD_SAY_HELLO_TO 1

//compalibility
#define HELLO_SVC_CMD_SAY_HELLO    1
#define HELLO_SVC_CMD_SAY_HELLO_TO 2
#define HELLO_SVC_CMD_GET_FD       3


#define HELLO_SERVER_DESCRIPTOR "IHelloService"

namespace android {

class IHelloService: public IInterface
{
public:
	DECLARE_META_INTERFACE(HelloService);

	virtual void sayhello(void) = 0;
	virtual int sayhello_to(const char * name)  = 0;
	virtual int get_fd(void) = 0;
	
};

class BnHelloService: public BnInterface<IHelloService>
{
private:
	int fd;
	
public:

	BnHelloService();
	BnHelloService(int fd);
	
	virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
	virtual void sayhello(void);
	virtual int sayhello_to(const char *name);
	virtual int get_fd(void);
};

}

#endif // ANDROID_IHELLOSERVICE_H

