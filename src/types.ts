export enum IdleState {
	active = 'active',
	idlePrevented = 'idle-prevented',
	idle = 'idle',
	locked = 'locked',
	unknown = 'unknown'
}

export interface Addon {
	getIdleState(idleThreshold: number): IdleState;
}
