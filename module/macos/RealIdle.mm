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
		int32_t idleSeconds = -1;
		io_iterator_t iter = 0;

		if (IOServiceGetMatchingServices(kIOMasterPortDefault, IOServiceMatching("IOHIDSystem"), &iter) == KERN_SUCCESS) {
			io_registry_entry_t entry = IOIteratorNext(iter);
			if (entry) {
				CFMutableDictionaryRef dict = NULL;
				if (IORegistryEntryCreateCFProperties(entry, &dict, kCFAllocatorDefault, 0) == KERN_SUCCESS) {
					CFNumberRef obj = reinterpret_cast<CFNumberRef>(CFDictionaryGetValue(dict, CFSTR("HIDIdleTime")));
					if (obj) {
						int64_t nanoseconds = 0;
						if (CFNumberGetValue(obj, kCFNumberSInt64Type, &nanoseconds)) {
							idleSeconds = static_cast<int32_t>(nanoseconds / NSEC_PER_SEC);
						}
					}
					CFRelease(dict);
				}
				IOObjectRelease(entry);
			}
			IOObjectRelease(iter);
		}

		return idleSeconds;
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
		else if (idleSeconds < idleThreshold) {
			return active;
		}

		if (getSystemIdlePrevented()) {
			return idlePrevented;
		}

		return idle;
	}
}
