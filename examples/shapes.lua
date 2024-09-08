
function setup()
   createWindow(600, 600);

   noStroke();
   fill(255, 160);
end

local angle = 0;
function draw()
   background(51);

   textSize(32)
   text('Various 2D shapes', 280, 60);
   

   for i=1, 8 do
      strokeWeight(5);
      circle(i * (i*i)/2 + 150, height/2, i*i)
   end

   stroke(0);
   for i=1, 8 do
      push();
      local size = i*i;
      translate(i * size/2 + 150, height/2 - size/2 - 50)
      fill(i*6, 130 - 6*i, size / 3);
      rotate(angle);
      strokeWeight(12);
      square(-size/2, -size/2, size);
      pop();
   end

   for i=1, 8 do
      push();
      local size = i*i;
      translate(i * size/2 + 150, height/2 + size/2 + 50)
      fill(size, 200 - 12*i, i*10);
      rotate(angle);
      rect(-size/2, -size/2  +5, size+10, size);
      pop();
   end

   for i=1, 8 do
      push();
      local size = i*i;
      translate(i * size/2 + 150, height/2 + size + 130)
      fill(200 - 12*i, size, i*10);
      rotate(angle);
      ellipse(0, 0, size, size * 1.6);
      pop();
   end

   push();
   translate(300, 500);
   rotate(angle)
   stroke(0);
   strokeWeight(24)
   fill(255, 0, 0);
   pop();

   push();
   translate(130, 50);
   strokeWeight(10);
   triangle(0,0, 100, 0, 50, 50)
   pop();

   push();
   translate(50, 50);
   quad(
      0, 0,
      0, 60,
      60, 70,
      50, 10
   )
   pop();

   angle = angle + 1;
end
