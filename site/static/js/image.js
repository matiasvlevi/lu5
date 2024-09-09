function set_image_size() {
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
    
    window.onresize = resize_images;

	// Record original height for all demo images
	let demoImages = document.querySelectorAll('.demo');
	demoImages.forEach(img => {
		img.originalHeight = img.height;
	});

	// Resize them to screen
	resize_images();
}