
function slider(x1,x2,y,value)
	push();
	strokeWeight(4);
	fill(255,255,255);

	line(x1,y,x2,y);
	circle(map(value,-100,100,x1,x2),y,15);
	pop();
end

function setup()
   createWindow(600, 600);
end

function draw()
  background(51);
	textSize(25);

	sliderValue = map(constrain(mouseX,50,250),50,250,-100,100);
	text("value: " .. sliderValue, 50, 80);
	slider(50,250,100,sliderValue);

	text("abs function:", 50, 180);
	slider(50,250,200,abs(sliderValue));

	text("map function:", 50, 280);
	slider(50,250,300,map(sliderValue,-100,100,-30,30));
	push();
	fill(255,0,0);
	circle(map(-40,-100,100,50,250),300,10);
	circle(map(40,-100,100,50,250),300,10);
	pop();

	text("constrain function:", 50, 380);
	slider(50,250,400,constrain(sliderValue,-60,60));
	push();
	fill(255,0,0);
	circle(map(-70,-100,100,50,250),400,10);
	circle(map(70,-100,100,50,250),400,10);
	pop();

	text("dist function:", 350, 80);
	x1 = 450;
	y1 = 250;
	x2 = constrain(mouseX,350,550);
	y2 = constrain(mouseY,150,350);
	text("distance: " .. floor(dist(x1,y1,x2,y2)), 350, 130);
	push();
	strokeWeight(4);
	fill(255,255,255);
	line(x1,y1,x2,y2);
	circle(x1,y1,15);
	circle(x2,y2,15);
	pop();


end
