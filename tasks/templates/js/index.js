let menu;
function closeMenu() {
	menu.classList.remove(['open']);
}
function openMenu() { 
	menu.classList.add(['open']);
}
function isOpen() { 
	return menu.classList.contains('open');
}

function toggleMenu() {
	if (isOpen()) {
		closeMenu();
	} else { 
		openMenu();
	}
}

document.addEventListener('DOMContentLoaded', function() {
    menu = document.getElementById('menu');

	if (window.innerWidth > 900) {
		openMenu();
		
		// Add animation delay after first open
		setTimeout(() => menu.style.transition = '0.25s');
	} else {
		menu.style.transition = '0.25s'
	}

    document.addEventListener('click', function(e) {
        if (isOpen() && !e.target.matches('.nav, .nav *, .menuItem, .menuItem *, .menuBtn, .menuBtn *')) {
            closeMenu();
        }
    });

	document.addEventListener('scroll', function() {
		setTimeout(closeMenu, 150);
	})
});