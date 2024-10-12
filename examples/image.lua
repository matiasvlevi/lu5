
local x = 200;
local y = 200;

local vx = 195;
local vy = 160;

local size = 128;

function setup()
	createWindow(800, 600);
   logo = loadImage('./images/logo.png');
end

function draw()
   background(51);

   image(logo, x, y, size, size);

   textSize(14);
   text('x: ' .. round(x) .. ' y: ' .. round(y), x, y);

   if (x >= width-size or x <= 0) then
      vx = -vx;
   end
   if (y >= height-size or y <= 0) then
      vy = -vy;
   end

   x = x + vx * deltaTime;
   y = y + vy * deltaTime;

   x = math.max(math.min(x, width-size), 0);
   y = math.max(math.min(y, height-size), 0);
end
