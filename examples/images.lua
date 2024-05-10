x = 20;
vx = 125;

y = 10;
vy = 90;

size = 48;

function setup()
	createWindow(400, 400);

	img = loadImage('./docs/assets/logo.png');
end

function draw()
	background(51);

	image(img, x, y, size, size);

	if (x > width-size or x < 0) then
		vx = -vx;
	end

	if (y > height-size or y < 0) then
		vy = -vy;
	end

	x = x + vx * deltaTime;
	y = y + vy * deltaTime;
end
