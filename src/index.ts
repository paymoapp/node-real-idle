import { Addon, IdleState } from './types';

const SUPPORTED_PLATFORMS = ['win32', 'linux', 'darwin'];

let addon: Addon | null = null;

if (SUPPORTED_PLATFORMS.includes(process.platform)) {
	addon = require('../build/Release/PaymoRealIdle.node'); // eslint-disable-line import/no-dynamic-require
}

export { IdleState };

export const getLocked = (): boolean => {
	if (!addon) {
		return false;
	}

	return addon.getLocked();
};

export const getIdleSeconds = (): number => {
	if (!addon) {
		return -1;
	}

	return addon.getIdleSeconds();
};

export const getIdlePrevented = (): boolean => {
	if (!addon) {
		return false;
	}

	return addon.getIdlePrevented();
};

export const getIdleState = (idleThreshold: number): IdleState => {
	if (!addon) {
		return IdleState.unknown;
	}

	return addon.getIdleState(idleThreshold);
};

const RealIdle = {
	getLocked,
	getIdleSeconds,
	getIdlePrevented,
	getIdleState
};

export default RealIdle;
