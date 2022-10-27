{
	"targets": [
		{
			"target_name": "PaymoRealIdle",
			"conditions": [
				["OS=='linux'", {
					"sources": {
						"module/NapiBindings.cpp",
						"module/linux/RealIdle.cpp"
					},
					"libraries": [
						"-lX11",
						"-lXext",
						"-lXss"
					]
				}],
				["OS=='mac'", {
					"sources": {
						"module/NapiBindings.cpp",
						"module/macos/RealIdle.cpp"
					},
					"libraries": [
						"-framework Foundation"
					]
				}],
				["OS=='win'", {
					"sources": [
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
