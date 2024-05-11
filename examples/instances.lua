
acc = 1;
bounce = 1.5;
ball_count = 300;

mouse_zone = 256

-- Ball list
balls = {}

-- Ball class
local Ball = class('Ball');

function Ball:init(x, y)
    self.x = x
    self.y = y
    self.vx = 0;
    self.vy = 0;
    self.r = 16;

    self.cr = math.random(155, 255);
    self.cg = math.random(0, 155);
    self.cb = math.random(155, 255);

    return self
end

function Ball:collision(others)
    local nx = self.x + self.vx * deltaTime;
    local ny = self.y + self.vy * deltaTime;

    if (ny < self.r or ny > height-self.r) then 
        self.vy = -self.vy; 
    end

    if (nx < self.r or nx > width-self.r) then
        self.vx = -self.vx;
    end

    for i, other in pairs(others) do
        local dx = self.x - other.x;
        local dy = self.y - other.y;
        local d = math.sqrt(dx*dx + dy*dy);

        if (d < 16) then
            self.vx = self.vx + dx * bounce;
            self.vy = self.vy + dy * bounce;
        end
    end

    local dx = nx - mouseX;
    local dy = ny - mouseY;
    local d = math.sqrt(dx*dx + dy*dy);
    if (d < 1.5+8+mouse_zone/2) then

        if (mouseIsPressed) then
            self.vx = self.vx + -dx * bounce/5;
            self.vy = self.vy + -dy * bounce/5;
        else
            self.vx = self.vx + dx * bounce/2;
            self.vy = self.vy + dy * bounce/2;
        end


    end


end

function Ball:move()
    self.vx = self.vx + math.random(-acc, acc);
    self.vy = self.vy + math.random(-acc, acc);

    self.vy = self.vy * 0.94;
    self.vx = self.vx * 0.94;

    self:collision(balls);

    self.x = self.x + self.vx * deltaTime;
    self.y = self.y + self.vy * deltaTime;
end 

function Ball:draw()
    strokeWeight(3);
    stroke(self.cr, self.cg, self.cb);
    fill(255, 255, 255, 25)
    circle(self.x, self.y, 16);
end



function setup() 
    createWindow(800, 600); 

    for i=1, ball_count do
      balls[i] = Ball:new(
            math.random(50, width-50),
            math.random(50, height-50)
        );
    end

    frameRate(60);

    logo = loadImage('docs/assets/lu5_icon.png');
end

function draw()
    background(51);

    for i,ball in pairs(balls) do
        ball:draw();
        ball:move();
    end

    circle(mouseX, mouseY, mouse_zone);

    textSize(18);
    fill(100, 255, 10);
    text(round(frameRate()) .. ' fps', 30, 10);
end
