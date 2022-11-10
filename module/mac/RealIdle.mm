#include "../RealIdle.h"
#import <Foundation/Foundation.h>
#import <ApplicationServices/ApplicationServices.h>
#include <IOKit/pwr_mgt/IOPMLib.h>

namespace PaymoRealIdle {
	bool getSystemLocked() {
		CFDictionaryRef sessionInfo = CGSessionCopyCurrentDictionary();

		if (sessionInfo == NULL) {
			return false;
		}

		CFBooleanRef sessionScreenIsLocked = reinterpret_cast<CFBooleanRef>(CFDictionaryGetValue(sessionInfo, CFSTR("CGSSessionScreenIsLocked")));

		bool isLocked = false;
		if (sessionScreenIsLocked != NULL && CFBooleanGetValue(sessionScreenIsLocked)) {
			isLocked = true;
		}

		CFRelease(sessionInfo);
		return isLocked;
	}

	int32_t getSystemIdleSeconds() {
		CFTimeInterval idleTime = CGEventSourceSecondsSinceLastEventType(kCGEventSourceStateCombinedSessionState, kCGAnyInputEventType);

		return static_cast<int32_t>(idleTime);
	}

	bool getSystemIdlePrevented() {
		bool idlePrevented = false;

		CFDictionaryRef dict;
		if (IOPMCopyAssertionsStatus(&dict) == kIOReturnSuccess) {
			CFNumberRef obj = reinterpret_cast<CFNumberRef>(CFDictionaryGetValue(dict, kIOPMAssertionTypePreventUserIdleDisplaySleep));
			if (obj) {
				int value = 0;
				if (CFNumberGetValue(obj, kCFNumberIntType, &value)) {
					if (value > kIOPMAssertionLevelOff) {
						idlePrevented = true;
					}
				}
			}
			CFRelease(dict);
		}

		return idlePrevented;
	}

	IdleState getSystemIdleState(int32_t idleThreshold) {
		if (getSystemLocked()) {
			return locked;
		}

		int32_t idleSeconds = getSystemIdleSeconds();

		if (idleSeconds == -1) {
			return unknown;
		}
		
		if (idleSeconds < idleThreshold) {
			return active;
		}

		if (getSystemIdlePrevented()) {
			return idlePrevented;
		}

		return idle;
	}
}
