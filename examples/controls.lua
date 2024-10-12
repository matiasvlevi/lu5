x = 300;
y = 300;
vx = 0;
vy = 0;


function setup()
	createWindow(600, 600);
end

function draw()
	background(51);

	text('Use the WASD keys to move the character around', 40, 40);

	if (keyIsDown('a')) then
		vx = vx - 10;
	end
	if (keyIsDown('d')) then
		vx = vx + 10;
	end
	if (keyIsDown('w')) then
		vy = vy - 10;
	end
	if (keyIsDown('s')) then
		vy = vy + 10;
	end

	fill(255);
	strokeWeight(6);
	circle(x, y, 32);

	line(x,y,x+vx/8,y+vy/8);

	x = x + vx * deltaTime;
	y = y + vy * deltaTime;

	vx = vx * 0.97;
	vy = vy * 0.97;

	print('Vel X:', vx, ' Vel Y:', vy)
end