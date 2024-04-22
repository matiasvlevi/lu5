
acc = 1;

Ball = {}
Ball.__index = Ball

function Ball.new(x, y)
    local self = setmetatable({}, Ball)
    self.x = x
    self.y = y
    self.vx = 0;
    self.vy = 0;
    self.r = 16;
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
    if (isKeyDown(KEY_RIGHT)) then
        self.vx = self.vx + acc;
    end

    if (isKeyDown(KEY_LEFT)) then
        self.vx = self.vx - acc;
    end
 
    if (isKeyDown(KEY_UP)) then
        self.vy = self.vy - acc;
    end

    if (isKeyDown(KEY_DOWN)) then
        self.vy = self.vy + acc;
    end
end

function Ball:draw()
    circle(self.x, self.y, 32);
end

balls = {}

function setup() 
    createWindow(800, 800); 

    for i=1, 10 do
      balls[i] = Ball.new(math.random(width),math.random(height))
    end

end

function draw()
    background(51);

    text(string.format("Count: %d", 2), 40, 30);

    for i,ball in pairs(balls) do --pseudocode
        ball:draw();
        ball:control();
        ball:move();
    end
end
