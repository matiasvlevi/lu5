
acc = 1;
ball_count = 50;

Ball = {}
Ball.__index = Ball

function Ball.new(x, y)
    local self = setmetatable({}, Ball)
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
    self.vy = self.vy * 0.96;
    self.vx = self.vx * 0.96;

    self:collision(self.x + self.vx, self.y + self.vy);

    self.x = self.x + self.vx;
    self.y = self.y + self.vy;
end 

function Ball:control()
    if (isKeyDown(RIGHT_ARROW)) then
        self.vx = self.vx + acc;
    end

    if (isKeyDown(LEFT_ARROW)) then
        self.vx = self.vx - acc;
    end
 
    if (isKeyDown(UP_ARROW)) then
        self.vy = self.vy - acc;
    end

    if (isKeyDown(DOWN_ARROW)) then
        self.vy = self.vy + acc;
    end
end

function Ball:draw()
    noFill();
    strokeWeight(2);
    stroke(self.cr, self.cg, self.cb);
    circle(self.x, self.y, 32);
end

balls = {}

function setup() 
    createWindow(1920, 1080); 

    for i=1, ball_count do
      balls[i] = Ball.new(
            math.random(50, width-50),
            math.random(50, height-50)
        );
    end
end

function draw()
    background(51);

    for i,ball in pairs(balls) do
        ball:draw();
        ball:control();
        ball:move();
    end
end
