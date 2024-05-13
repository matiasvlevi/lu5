range = 16;
amplitude = 6;

step = TWO_PI/128;

function setup()
	createWindow(400, 400);
end

function draw()
	background(51);

	fill(205, 190, 40);

	vertex(mouseX, mouseY);
	beginShape(TRIANGLE_FAN);
		for i=0, TWO_PI, step do

			local size = 12 + amplitude*((i/step) % range);

			vertex(
				size * cos(i) + mouseX,
				size * sin(i) + mouseY
			)
		end
	endShape();

end
