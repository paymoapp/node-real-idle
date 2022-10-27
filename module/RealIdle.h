#include <napi.h>

#ifndef _PAYMO_REALIDLE_H
#define _PAYMO_REALIDLE_H

namespace PaymoRealIdle {
	enum IdleState {
		active,
		idlePrevented,
		idle,
		locked,
		unknown
	};

	Napi::Object Init(Napi::Env env, Napi::Object exports);

	// exported functions
	Napi::String getIdleState(const Napi::CallbackInfo& info);

	// internal functions
	IdleState getSystemIdleState(int32_t idleThreshold);
}

#endif
