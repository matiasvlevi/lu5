
function setup()
   createWindow(600, 600);

   noStroke();
   fill(255, 160);
end

local angle = 0;
function draw()
   background(51);
   
   for i=1, 8 do
      circle(i * (i*i)/2 + 150, height/2, i*i)
   end

   stroke(0);
   for i=1, 8 do
      push();
      local size = i*i;
      translate(i * size/2 + 150, height/2 - size/2 - 50)
      fill(i*6, 130 - 6*i, size / 3);
      rotate(angle);
      strokeWeight(30);
      square(-size/2, -size/2, size);
      pop();
   end

   for i=1, 8 do
      push();
      local size = i*i;
      translate(i * size/2 + 150, height/2 + size/2 + 50)
      fill(size, 200 - 12*i, i*10);
      rotate(angle);
      rect(-size/2, -size/2, size, size);
      pop();
   end

   angle = angle + 1;
end
