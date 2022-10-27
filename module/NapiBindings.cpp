#include "RealIdle.h"

namespace PaymoRealIdle {
	Napi::Object Init(Napi::Env env, Napi::Object exports) {
		exports.set("getIdleState", Napi::Function::New(env, getIdleState));

		return exports;
	}

	Napi::String getIdleState(const Napi::CallbackInfo& info) {
		if (info.Length() != 1) {
			Napi::TypeError::New(info.Env(), "Expected 1 argument").ThrowAsJavaScriptException();
			return Napi::String::New(info.Env(), "unknown");
		}

		if (!info[0].IsNumber()) {
			Napi::TypeError::New(info.Env(), "Expected first argument to be a number").ThrowAsJavaScriptException();
			return Napi::String::New(info.Env(), "unknown");
		}

		unsigned int idleThreshold = info[0].As<Napi::Number>().Uint32Value();

		switch (getSystemIdleState(idleThreshold)) {
			case IdleState.active:
				return Napi::String::New(info.Env(), "active");
			case IdleState.idle:
				return Napi::String::New(info.Env(), "idle");
			case IdleState.idlePrevented:
				return Napi::String::New(info.Env(), "idle-prevented");
			case IdleState.locked:
				return Napi::String::New(info.Env(), "locked");
			default:
				return Napi::String::New(info.Env(), "unknown");
		}
	}
}
