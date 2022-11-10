#include "RealIdle.h"

namespace PaymoRealIdle {
	Napi::Object Init(Napi::Env env, Napi::Object exports) {
		exports.Set("getLocked", Napi::Function::New(env, getLocked));
		exports.Set("getIdleSeconds", Napi::Function::New(env, getIdleSeconds));
		exports.Set("getIdlePrevented", Napi::Function::New(env, getIdlePrevented));
		exports.Set("getIdleState", Napi::Function::New(env, getIdleState));

		return exports;
	}

	Napi::Boolean getLocked(const Napi::CallbackInfo& info) {
		return Napi::Boolean::New(info.Env(), getSystemLocked());
	}

	Napi::Number getIdleSeconds(const Napi::CallbackInfo& info) {
		return Napi::Number::New(info.Env(), getSystemIdleSeconds());
	}

	Napi::Boolean getIdlePrevented(const Napi::CallbackInfo& info) {
		return Napi::Boolean::New(info.Env(), getSystemIdlePrevented());
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

		int32_t idleThreshold = info[0].As<Napi::Number>().Int32Value();

		if (idleThreshold < 0) {
			Napi::TypeError::New(info.Env(), "Expected idleThreshold to be greater than 0").ThrowAsJavaScriptException();
			return Napi::String::New(info.Env(), "unknown");
		}

		switch (getSystemIdleState(idleThreshold)) {
			case active:
				return Napi::String::New(info.Env(), "active");
			case idle:
				return Napi::String::New(info.Env(), "idle");
			case idlePrevented:
				return Napi::String::New(info.Env(), "idle-prevented");
			case locked:
				return Napi::String::New(info.Env(), "locked");
			default:
				return Napi::String::New(info.Env(), "unknown");
		}
	}
}
