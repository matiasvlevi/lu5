range = 16;
amplitude = 6;

step = TWO_PI/128;

function setup()
	createWindow(400, 400);
end

function draw()
	background(51);

	fill(205, 190, 40);

	beginShape(TRIANGLE_FAN);
		vertex(mouseX, mouseY);
		
		for i = 0, TWO_PI, step do
			vertex(mouseX + cos(i) * 10 * random(9.0, 10.0), mouseY + sin(i) * 10 * random(9.0, 10.0));
		end
	endShape();

end
