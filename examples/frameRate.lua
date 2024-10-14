x = 100
vx = 7;

function setup()
	createWindow(400, 400);
	
	-- Lock fps
	frameRate(20);
end

function draw()
	background(51);
	
	-- render fps
	text('fps: ' .. frameRate(), 20, 40);

	-- render circle
	circle(x, 200, 32);

	-- bounce
	if (x > width-16 or x < 16) then
		print('wall hit !')
		vx = -vx;
	end

	-- move
	x = x + vx;
end
