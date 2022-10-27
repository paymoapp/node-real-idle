import { Addon, IdleState } from './types';

const SUPPORTED_PLATFORMS = ['win32', 'linux', 'darwin'];

let addon: Addon | null = null;

if (SUPPORTED_PLATFORMS.includes(process.platform)) {
	addon = require('../build/Release/PaymoRealIdle.node'); // eslint-disable-line import/no-dynamic-require
}

export { IdleState };
export const getIdleState = (idleThreshold: number): IdleState => {
	if (!addon) {
		return IdleState.unknown;
	}

	return addon.getIdleState(idleThreshold);
};

const RealIdle = {
	getIdleState
};

export default RealIdle;
