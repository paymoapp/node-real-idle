export enum IdleState {
	active = 'active',
	idlePrevented = 'idle-prevented',
	idle = 'idle',
	locked = 'locked',
	unknown = 'unknown'
}

export interface Addon {
	getLocked(): boolean;
	getIdleSeconds(): number;
	getIdlePrevented(): boolean;
	getIdleState(idleThreshold: number): IdleState;
}
