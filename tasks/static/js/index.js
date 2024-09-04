function get_os() {
	const userAgent = window.navigator.userAgent,
		platform = window.navigator?.userAgentData?.platform || window.navigator.platform,
		macosPlatforms = ['macOS', 'Macintosh', 'MacIntel', 'MacPPC', 'Mac68K'],
		windowsPlatforms = ['Win32', 'Win64', 'Windows', 'WinCE'],
		iosPlatforms = ['iPhone', 'iPad', 'iPod'];
	let os = null;

	if (macosPlatforms.indexOf(platform) !== -1) {
		os = 'Mac';
	} else if (iosPlatforms.indexOf(platform) !== -1) {
		os = null;
	} else if (windowsPlatforms.indexOf(platform) !== -1) {
		os = 'Windows';
	} else if (/Android/.test(userAgent)) {
		os = null;
	} else if (/Linux/.test(platform)) {
		os = 'Linux';
	}

	return os;
}

let menu;
const reactives = [];
function closeMenu(e) {
	e.classList.remove(['open']);
}
function openMenu(e) {
	e.classList.add(['open']);
}
function isOpen(e) {
	return e.classList.contains('open');
}

function toggleMenu() {
	if (isOpen(menu)) {

		reactives.forEach(closeMenu);
		closeMenu(menu);
	} else {
		console.log(reactives);
		reactives.forEach(openMenu);
		openMenu(menu);
	}
}

function resize_images() {
	if (innerWidth < 600) {
		let demoImages = document.querySelectorAll('.demo');
		demoImages.forEach(img => {
			img.height = img.originalHeight / 1.5;
		});
	} else {
		let demoImages = document.querySelectorAll('.demo');
		demoImages.forEach(img => {
			if (img.originalHeight) img.height = img.originalHeight;
		});
	}

}

window.onresize = function(e) {
	console.log(e);
	resize_images()
};

function main() {
	let platform = get_os();

	if (platform != null) {
		let downloadElem = document.getElementById(`download-${platform}`);
		downloadElem.id = `-download-${platform}`;

		console.log(downloadElem);
	} else {
		let downloadElem = document.getElementById(`download-fallback`);
		downloadElem.id = '-download-fallback';
	}
	
	// Record original height for all demo images
	let demoImages = document.querySelectorAll('.demo');
	demoImages.forEach(img => {
		img.originalHeight = img.height;
	});

	// Resize them to screen
	resize_images();

	let menu = document.getElementById('menu');
	if (window.innerWidth > 900) {

		reactives.forEach(openMenu);
		openMenu(menu);

		// Add animation delay after first open
		setTimeout(() => menu.style.transition = '0.25s');
	} else {
		menu.style.transition = '0.25s'
	}

	document.addEventListener('click', function (e) {
		if (isOpen(menu) && !e.target.matches('.nav, .nav *, .menuItem, .menuItem *, .menuBtn, .menuBtn *')) {
			reactives.forEach(closeMenu);
			closeMenu(menu);
		}
	});

	document.querySelectorAll('#reactive').forEach(elem => {
		console.log(elem);
		reactives.push(elem);
	});

	document.addEventListener('scroll', function () {
		setTimeout(() => {
			reactives.forEach(closeMenu);
			closeMenu(menu);
		}, 150);
	})
}