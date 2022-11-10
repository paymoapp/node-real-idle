#include "../RealIdle.h"
#include <windows.h>

namespace PaymoRealIdle {
	bool getSystemLocked() {
		return false;
	}

	int32_t getSystemIdleSeconds() {
		LASTINPUTINFO lastInput;
		lastInput.cbSize = sizeof(lastInput);

		if (!GetLastInputInfo(&lastInput)) {
			return -1;
		}

		uint64_t tickCount = GetTickCount64();

		return (tickCount - (uint64_t)lastInput.dwTime) / 1000;
	}

	bool getSystemIdlePrevented() {
		return false;
	}

	IdleState getSystemIdleState(int32_t idleThreshold) {
		// locked screen is not supported
		
		int32_t idleSeconds = getSystemIdleSeconds();

		if (idleSeconds == -1) {
			return unknown;
		}

		if (idleSeconds < idleThreshold) {
			return active;
		}

		// idle prevented not supported

		return idle;
	}
}
