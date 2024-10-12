
size = 40;
logo_count = 100;

mouse_zone = 300

-- Logos list
logos = {}

-- Logo class
local Logo = class('Logo');

function Logo:init(x, y, vx, vy)
    self.x = x
    self.y = y
    self.vx = vx;
    self.vy = vy;
    self.size = size;

    return self;
end

function Logo:collision(others)
    local nx = self.x + self.vx * deltaTime;
    local ny = self.y + self.vy * deltaTime;

    if (ny < 0 or ny > height-self.size) then 
        self.vy = -self.vy; 
    end

    if (nx < 0 or nx > width-self.size) then
        self.vx = -self.vx;
    end
end

function Logo:move()
    self:collision(balls);

    self.x = self.x + self.vx * deltaTime;
    self.y = self.y + self.vy * deltaTime;
end

function Logo:draw()
    fill(255, 150);
    image(img, self.x, self.y, self.size, self.size);
end

function setup() 
    createWindow(800, 600); 

    for i=1, logo_count do
      logos[i] = Logo:new(
            math.random(50, width-50),
            math.random(50, height-50),
            math.random(-100, 100),
            math.random(-100, 100)
        );
    end

    img = loadImage('./images/logo.png');

    frameRate(60);
end

function draw()
    background(51);

    for i,logo in pairs(logos) do
        logo:draw();
        logo:move();
    end
end
