# @paymoapp/real-idle

[![NPM](https://img.shields.io/npm/v/@paymoapp/node-real-idle)](https://www.npmjs.com/package/@paymoapp/node-real-idle)
[![Typescript](https://img.shields.io/npm/types/@paymoapp/node-real-idle)](https://www.npmjs.com/package/@paymoapp/node-real-idle)
[![N-API](https://raw.githubusercontent.com/nodejs/abi-stable-node/doc/assets/Node-API%20v6%20Badge.svg)](https://github.com/nodejs/node-addon-api)
[![License](https://img.shields.io/github/license/paymoapp/node-real-idle)](https://www.gnu.org/licenses/gpl-3.0.txt)

NodeJS library using native modules to detect the real idle state of the system.

### Table of Contents

<!-- toc -->

- [What this library does](#what-this-library-does)
- [Getting started](#getting-started)
    - [Installation](#installation)
    - [Native addon](#native-addon)
    - [Example](#example)
- [API](#api)
    - [Functions](#functions)
    - [Enums](#enums)
- [Platform support](#platform-support)
    - [Supported functions](#supported-functions)
    - [Supported idle states](#supported-idle-states)
    - [Default values](#default-values)

<!-- tocstop -->

## What this library does

Sometimes it's not enough to know how long ago was the last input event from the user to determine the idle state of the system.

This library can detect on mac and linux if there's a background activity running (for example: watching a video or participating in a zoom meeting) in which case the user shouldn't be treated as idle.

This is done by requesting the IOPM Assertions (on mac) and using the IsInhibited DBUS function (on linux).

## Getting started

#### Installation

```bash
npm install --save @paymoapp/real-idle
```

#### Native addon

This project uses NodeJS Native Addons to function, so you can use this library in any NodeJS or Electron project, there won't be any problem with bundling and code signing.

The project uses [prebuild](https://github.com/prebuild/prebuild) to supply prebuilt libraries.

The project uses Node-API version 6, you can check [this table](https://nodejs.org/api/n-api.html#node-api-version-matrix) to see which node versions are supported.

If there's a compliant prebuilt binary, it will be downloaded during installation, or it will be built. You can also rebuild it anytime by running `npm run build:gyp`.

The library has native addons for Windows, MacOS and Linux.

#### Example

You can run a demo application by calling `npm run demo` and you can tweak the parameters in the `demo/electron.js` file. For the demo it is required to start an electron application since on MacOS a GUI session is required to access some functions (although you might get it working in a console application as well).

```ts
import RealIdle from '@paymoapp/real-idle';

setTimeout(() => {
	console.log('System idle state:', RealIdle.getIdleState(300));
	console.log('  - Idle seconds:', RealIdle.getIdleSeconds());
	console.log('  - Is screen locked:', RealIdle.getLocked());
	console.log('  - Is idle prevented:', RealIdle.getIdlePrevented());
}, 5000);
```

## API

#### Functions

###### 𝑓 &nbsp;&nbsp; getLocked

```ts
type getLocked = () => boolean
```

Returns true if the screen is locked and false if the screen is unlocked or if the function is not available on the current operating system.

__Supported on:__ MacOS

###### 𝑓 &nbsp;&nbsp; getIdleSeconds

```ts
type getIdleSeconds = () => number
```

Returns the system idle time _in seconds_, or -1 if the library couldn't fetch this value.

__Supported on:__ Windows, MacOS, Linux (X11)

###### 𝑓 &nbsp;&nbsp; getIdlePrevented

```ts
type getIdlePrevented = () => boolean
```

Returns true if the system idle is prevented (the screen would not automatically dim/lock). This is mostly the cause of having a video playing back in the front, attending a metting, etc. The function returns false if no assertion or inhibitor is set or if the function is not available on the current operating system.

__Supported on:__ MacOS, Linux (X11 and Gnome, but some other desktop environments should work too)

###### 𝑓 &nbsp;&nbsp; getIdleState

```ts
type getIdleState = (idleThreshold: number): IdleState
```

Returns the idle state of the system based on the idle threshold (in seconds). It's supported on all operating systems, but see the [Platform support](#platform-support) section for the possible return values.

__Supported on:__ Windows, MacOS, Linux (X11 and Gnome, but some other desktop environments should work too)

#### Enums

###### 📋 &nbsp;&nbsp; IdleState

```ts
enum IdleState {
	active = 'active',
	idlePrevented = 'idle-prevented',
	idle = 'idle',
	locked = 'locked',
	unknown = 'unknown'
}
```

Meaning:

- _active_: The user is actively using the system.
- _idlePrevented_: Something (video playback, meeting, etc) is preventing the system from dimming the screen and locking it. The user may not input events to the system, but he/she is probably using it.
- _idle_: The user is idle.
- _locked_: The system is locked.
- _unknown_: We failed to fetch some parameter or the library is not available for the current operating system.

## Platform support

#### Supported functions

| Function / Platform  | Windows | MacOS | Linux |
|----------------------|---------|-------|-------|
| `getLocked()`        | NO      | YES   | NO    |
| `getIdleSeconds()`   | YES     | YES   | YES   |
| `getIdlePrevented()` | NO      | YES   | YES   |
| `getIdleState()`     | YES\*   | YES   | YES\* |

_\* See supported idle states below_

#### Supported idle states

| State / Platform | Windows | MacOS | Linux |
|------------------|---------|-------|-------|
| `active`         | YES     | YES   | YES   |
| `idlePrevented`  | NO      | YES   | YES   |
| `idle`           | YES     | YES   | YES   |
| `locked`         | NO      | YES   | NO    |
| `unknown`        | YES     | YES   | YES   |

#### Default values

Even if a function/idle state is unsupported on a specific platform, you can safely call them. They will just return the default value for that function.

| Function             | Default value |
|----------------------|---------------|
| `getLocked()`        | `false`       |
| `getIdleSeconds()`   | `-1`          |
| `getIdlePrevented()` | `false`       |
| `getIdleState()`     | `'unknown'`   |
