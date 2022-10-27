#include <napi.h>
#include "RealIdle.h"

namespace PaymoRealIdleModule {
	Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
		return PaymoRealIdle::Init(env, exports);
	}
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, PaymoRealIdleModule::InitAll);
