
acc = 25;
ball_count = 256;

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

function Ball:collision(nx, ny)
    if (ny < self.r or ny > height-self.r) then 
        self.vy = -self.vy; 
    end

    if (nx < self.r or nx > width-self.r) then
        self.vx = -self.vx;
    end
end

function Ball:move()
    self.vx = self.vx + math.random(-5, 5);
    self.vy = self.vy + math.random(-5, 5);

    self.vy = self.vy * 0.97;
    self.vx = self.vx * 0.97;

    local nvx = self.vx * deltaTime;
    local nvy = self.vy * deltaTime;

    self:collision(self.x + self.vx * deltaTime, self.y + self.vy * deltaTime);

    self.x = self.x + self.vx * deltaTime;
    self.y = self.y + self.vy * deltaTime;
end 

function Ball:draw()
    noFill();
    strokeWeight(2);
    stroke(self.cr, self.cg, self.cb);
    circle(self.x, self.y, 16);
end

balls = {}

function setup() 
    createWindow(600, 600); 

    for i=1, ball_count do
      balls[i] = Ball:new(
            math.random(50, width-50),
            math.random(50, height-50)
        );
    end

    frameRate(60);
end

function draw()
    background(51);

    for i,ball in pairs(balls) do
        ball:draw();
        ball:move();
    end

    textSize(18);
    fill(0, 255, 100);
    text(round(frameRate()) .. ' fps', 30, 10);
end
