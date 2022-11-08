{
	"targets": [
		{
			"target_name": "PaymoRealIdle",
			"conditions": [
				["OS=='linux'", {
					"sources": [
						"module/main.cpp",
						"module/NapiBindings.cpp",
						"module/linux/RealIdle.cpp"
					],
					"libraries": [
						"-lX11",
						"-lXext",
						"-lXss",
						"-ldbus-1"
					],
					"cflags": [
						"<!(pkg-config --cflags dbus-1)"
					]
				}],
				["OS=='mac'", {
					"sources": [
						"module/main.cpp",
						"module/NapiBindings.cpp",
						"module/macos/RealIdle.mm"
					],
					"libraries": [
						"-framework Foundation",
						"-framework ApplicationServices",
						"-framework IOKit"
					]
				}],
				["OS=='win'", {
					"sources": [
						"module/main.cpp",
						"module/NapiBindings.cpp",
						"module/win/RealIdle.cpp"
					],
					"libraries": [
						"User32.dll"
					]
				}]
			],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			"libraries": [],
			"dependencies": [
				"<!(node -p \"require('node-addon-api').gyp\")"
			],
			"defines": [
				"NAPI_DISABLE_CPP_EXCEPTIONS",
				"NAPI_VERSION=<(napi_build_version)"
			]
		}
	]
}
