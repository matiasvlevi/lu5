
function setup()
   createWindow(600, 600);

   noStroke();
   fill(255, 160);
end


function draw()
   background(51);
   
   for i=1, 8 do
      circle(i * (i*i)/2 + 150, height/2, i*i)
   end
end
