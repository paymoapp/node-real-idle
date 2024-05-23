# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

### [1.1.1](https://github.com/paymoapp/node-real-idle/compare/v1.1.0...v1.1.1) (2024-05-23)


### Build/CI

* Removed msvs version from build scripts ([291d1d1](https://github.com/paymoapp/node-real-idle/commit/291d1d1c4305585625ade06a4a96b781bfcb0f49))

## [1.1.0](https://github.com/paymoapp/node-real-idle/compare/v1.0.6...v1.1.0) (2024-05-23)


### Features

* Replace license with MIT ([0bea116](https://github.com/paymoapp/node-real-idle/commit/0bea1162193c3f57fd93f624e0820d6370a27b52))

### [1.0.6](https://github.com/paymoapp/node-real-idle/compare/v1.0.5...v1.0.6) (2024-01-19)


### Documentation

* fix minor typos and improve grammar in readme file ([d27b270](https://github.com/paymoapp/node-real-idle/commit/d27b270bd82e2c724103d49dc8871d40cd849bee))

### [1.0.5](https://github.com/paymoapp/node-real-idle/compare/v1.0.4...v1.0.5) (2023-10-13)


### Build/CI

* **gitlab:** Use new runners ([7be6e4e](https://github.com/paymoapp/node-real-idle/commit/7be6e4e7cd0f661d710d58a0b3a46e0ff8d24505))

### [1.0.4](https://github.com/paymoapp/node-real-idle/compare/v1.0.3...v1.0.4) (2023-10-13)


### Improvements

* **module:** Changed the way methods are exported ([3eb4fd0](https://github.com/paymoapp/node-real-idle/commit/3eb4fd0711c6507f393ba3a87ba6d71babd73cf9))


### Build/CI

* **gitlab:** Set xcode build tools and msvs versions from variables ([47e8c7f](https://github.com/paymoapp/node-real-idle/commit/47e8c7f22f94f64066c540bea76aecf46e72211c))

### [1.0.3](https://github.com/paymoapp/node-real-idle/compare/v1.0.2...v1.0.3) (2023-05-22)


### Bug Fixes

* **module.linux:** Check if we couldn't allocate a dbus message to avoid segfaults ([93d764d](https://github.com/paymoapp/node-real-idle/commit/93d764d780ab6b80171a0448a28247c221c29e66))

### [1.0.2](https://github.com/paymoapp/node-real-idle/compare/v1.0.1...v1.0.2) (2022-11-10)


### Documentation

* Fixed badges ([3323f20](https://github.com/paymoapp/node-real-idle/commit/3323f20895b5d6e0361c6f2536c0fece6cfb9dcb))

### [1.0.1](https://github.com/paymoapp/node-real-idle/compare/v1.0.0...v1.0.1) (2022-11-10)

## 1.0.0 (2022-11-10)


### Features

* Added ts glue and demo ([3b05367](https://github.com/paymoapp/node-real-idle/commit/3b0536724ac0d743dfd85942e458f29aff7d6f49))
* Exposed internal functions to allow getting the components of the idle state ([3625cca](https://github.com/paymoapp/node-real-idle/commit/3625cca4f7623617b86a9245d0ef4407c5e75d14))
* **module.linux:** Implemented native code for Linux using xscreensaver and dbus ([ea2b17e](https://github.com/paymoapp/node-real-idle/commit/ea2b17e12113cb71c585455e13affb2b75fad36d))
* **module.macos:** Implemented native code for macOS ([d1b6882](https://github.com/paymoapp/node-real-idle/commit/d1b688252b57821db9a34e84b18c1fa669bf7838))
* **module.windows:** Implemented native code for Windows ([b825ea9](https://github.com/paymoapp/node-real-idle/commit/b825ea9ffbfd9b2ba17ead00076b5ad2ce9c87f9))


### Improvements

* **module.macos:** Simplified getSystemIdleSeconds function based on Chromium source code ([b141246](https://github.com/paymoapp/node-real-idle/commit/b141246ac43604e008ece55e59714c66b42d29e4))


### Build/CI

* Added build configuration ([e3f525d](https://github.com/paymoapp/node-real-idle/commit/e3f525de177b8769962cd002664ee6befae3d6fc))


### Documentation

* Added documentation ([803a0d0](https://github.com/paymoapp/node-real-idle/commit/803a0d05f84707dea1428eb72335e61a6c496067))
