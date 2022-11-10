const { app, BrowserWindow } = require('electron');
const RealIdle = require('../dist').default;

const POLL_INTERVAL = 10;
const IDLE_THRESHOLD = 30;

app.whenReady().then(() => {
	const win = new BrowserWindow({
		width: 600,
		height: 400,
		title: 'Real-idle demo'
	});

	win.loadFile('index.html');

	console.log('--- Real-idle demo ---');

	console.log(`Idle threshold is set to ${IDLE_THRESHOLD} seconds`);
	console.log(`Polling idle state in every ${POLL_INTERVAL} seconds`);

	setInterval(() => {
		console.log(
			'Current idle state:',
			RealIdle.getIdleState(IDLE_THRESHOLD)
		);
		console.log(' - Locked:', RealIdle.getLocked());
		console.log(' - Idle seconds:', RealIdle.getIdleSeconds());
		console.log(' - Idle prevented:', RealIdle.getIdlePrevented());
	}, POLL_INTERVAL * 1000);
});
