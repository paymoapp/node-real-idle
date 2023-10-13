#include "RealIdle.h"

namespace PaymoRealIdle {
	void Init(Napi::Env env, Napi::Object exports) {
		exports.Set("getLocked", Napi::Function::New<getLocked>(env));
		exports.Set("getIdleSeconds", Napi::Function::New<getIdleSeconds>(env));
		exports.Set("getIdlePrevented", Napi::Function::New<getIdlePrevented>(env));
		exports.Set("getIdleState", Napi::Function::New<getIdleState>(env));
	}

	Napi::Value getLocked(const Napi::CallbackInfo& info) {
		Napi::Env env = info.Env();

		return Napi::Boolean::New(env, getSystemLocked());
	}

	Napi::Value getIdleSeconds(const Napi::CallbackInfo& info) {
		Napi::Env env = info.Env();

		return Napi::Number::New(env, getSystemIdleSeconds());
	}

	Napi::Value getIdlePrevented(const Napi::CallbackInfo& info) {
		Napi::Env env = info.Env();

		return Napi::Boolean::New(env, getSystemIdlePrevented());
	}

	Napi::Value getIdleState(const Napi::CallbackInfo& info) {
		Napi::Env env = info.Env();

		if (info.Length() != 1) {
			Napi::TypeError::New(env, "Expected 1 argument").ThrowAsJavaScriptException();
			return env.Null();
		}

		if (!info[0].IsNumber()) {
			Napi::TypeError::New(env, "Expected first argument to be a number").ThrowAsJavaScriptException();
			return env.Null();
		}

		int32_t idleThreshold = info[0].As<Napi::Number>().Int32Value();

		if (idleThreshold < 0) {
			Napi::TypeError::New(env, "Expected idleThreshold to be greater than 0").ThrowAsJavaScriptException();
			return env.Null();
		}

		switch (getSystemIdleState(idleThreshold)) {
			case active:
				return Napi::String::New(env, "active");
			case idle:
				return Napi::String::New(env, "idle");
			case idlePrevented:
				return Napi::String::New(env, "idle-prevented");
			case locked:
				return Napi::String::New(env, "locked");
			default:
				return Napi::String::New(env, "unknown");
		}
	}
}
