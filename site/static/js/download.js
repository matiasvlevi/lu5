function set_download_frontend() {

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

	let platform = get_os();

	if (platform != null) {
		let downloadElem = document.getElementById(`download-${platform}`);
		if (downloadElem) downloadElem.id = `-download-${platform}`;
	} else {
		let downloadElem = document.getElementById(`download-fallback`);
		if (downloadElem) downloadElem.id = '-download-fallback';
	}
}