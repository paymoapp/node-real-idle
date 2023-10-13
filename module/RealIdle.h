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

	void Init(Napi::Env env, Napi::Object exports);

	// exported functions
	Napi::Value getLocked(const Napi::CallbackInfo& info);
	Napi::Value getIdleSeconds(const Napi::CallbackInfo& info);
	Napi::Value getIdlePrevented(const Napi::CallbackInfo& info);
	Napi::Value getIdleState(const Napi::CallbackInfo& info);

	// internal functions
	bool getSystemLocked();
	int32_t getSystemIdleSeconds();
	bool getSystemIdlePrevented();
	IdleState getSystemIdleState(int32_t idleThreshold);
}

#endif
