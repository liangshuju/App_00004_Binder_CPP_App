

/*
 * reference : frameworks/av/inclue/media/IMediaPlayerService.h
*/

#ifndef ANDROID_IGOODBYESERVICE_H
#define ANDROID_IGOODBYESERVICE_H

#include <utils/Errors.h> // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>

#include <binder/IInterface.h>
#include <binder/Parcel.h>

#if 0
#define GOODBYE_SVC_CMD_SAY_GOODBYE    0
#define GOODBYE_SVC_CMD_SAY_GOODBYE_TO 1
#else // compatible java binder os
#define GOODBYE_SVC_CMD_SAY_GOODBYE    1
#define GOODBYE_SVC_CMD_SAY_GOODBYE_TO 2
#endif

#define GOODBYE_SERVOCE_DESCRIPTOR "IGoodbyeService"

namespace android {

class IGoodbyeService: public IInterface
{
public:
	DECLARE_META_INTERFACE(GoodbyeService);

	virtual void saygoodbye(void) = 0;
	virtual int saygoodbye_to(const char * name)  = 0;
	
};

class BnGoodbyeService: public BnInterface<IGoodbyeService>
{
public:
	virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);

	virtual void saygoodbye(void);
	virtual int saygoodbye_to(const char *name);
};

}

#endif // ANDROID_IGOODBYESERVICE_H

