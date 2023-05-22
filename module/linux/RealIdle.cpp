#include "../RealIdle.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/scrnsaver.h>
#include <dbus/dbus.h>

namespace PaymoRealIdle {
	int hasScreensaverExtension = -1;

	bool getSystemLocked() {
		return false;
	}

	int32_t getSystemIdleSeconds() {
		Display* display = XOpenDisplay(NULL);
		
		if (!display) {
			return -1;
		}

		if (hasScreensaverExtension == -1) {
			int _eventBase;
			int _errorBase;
			hasScreensaverExtension = XScreenSaverQueryExtension(display, &_eventBase, &_errorBase);
		}

		if (!hasScreensaverExtension) {
			XCloseDisplay(display);
			return -1;
		}

		Window window = RootWindow(display, DefaultScreen(display));

		if (!window) {
			XCloseDisplay(display);
			return 60*60*1000;
		}

		XScreenSaverInfo info;
		XScreenSaverQueryInfo(display, window, &info);

		XCloseDisplay(display);
		return info.idle / 1000;
	}

	bool getSystemIdlePrevented() {
		DBusError err;
		dbus_error_init(&err);

		DBusConnection* conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
		if (conn == NULL) {
			return false;
		}

		DBusMessage* msg = dbus_message_new_method_call("org.gnome.SessionManager", "/org/gnome/SessionManager", "org.gnome.SessionManager", "IsInhibited");
		if (msg == NULL) {
			return false;
		}

		DBusMessageIter args;
		dbus_message_iter_init_append(msg, &args);
		dbus_uint32_t inhibitFlag = 8;
		if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &inhibitFlag)) {
			dbus_message_unref(msg);
			return false;
		}

		DBusMessage* resp = dbus_connection_send_with_reply_and_block(conn, msg, 300, &err);
		dbus_message_unref(msg);
		if (resp == NULL) {
			return false;
		}

		if (!dbus_message_iter_init(resp, &args)) {
			dbus_message_unref(resp);
			return false;
		}

		bool isIdlePrevented = false;
		if (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_BOOLEAN) {
			dbus_message_unref(resp);
			return false;
		}
		dbus_message_iter_get_basic(&args, &isIdlePrevented);

		dbus_message_unref(resp);
		return isIdlePrevented;
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

		if (getSystemIdlePrevented()) {
			return idlePrevented;
		}

		return idle;
	}
}
