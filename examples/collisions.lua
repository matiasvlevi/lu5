
bounce = 2.5;
radius = 16;
ball_count = 140;

mouse_zone = 400

-- Ball list
balls = {}

-- Ball class
local Ball = class('Ball');

function Ball:init(x, y, vx, vy)
    self.x = x
    self.y = y
    self.vx = vx;
    self.vy = vy;
    self.r = radius;

    self.cr = random(155, 255);
    self.cg = random(0, 155);
    self.cb = random(155, 255);

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

        if (d < radius*2 + 1) then
            local dot = (-dx * self.vx/deltaTime)/width + (-dy * self.vy/deltaTime)/height;
            
            if (dot > 0) then
                dot = math.min(dot*8, 32) / 16;
                self.vx  = self.vx + dx * dot;
                self.vy  = self.vy + dy * dot;
                other.vx = other.vx + -dx * dot;
                other.vy = other.vy + -dy * dot;
            end
        end
    end

    local dx = nx - mouseX;
    local dy = ny - mouseY;
    local d = math.sqrt(dx*dx + dy*dy);
    if (d < 3+radius+(mouse_zone/2)) then

        if (mouseIsPressed) then
            self.vx = self.vx + -dx * bounce/3;
            self.vy = self.vy + -dy * bounce/3;
        else
            self.vx = self.vx + dx * bounce/2;
            self.vy = self.vy + dy * bounce/2;
        end


    end


end

function Ball:move()

    self:collision(balls);
    self.x = self.x + self.vx * deltaTime;
    self.y = self.y + self.vy * deltaTime;

    self.x = max(min(self.x, width-radius), radius);
    self.y = max(min(self.y, height-radius), radius);

    self.vy = self.vy * 0.8;
    self.vx = self.vx * 0.8;

end 


function Ball:draw()
    push();
    strokeWeight(3);
    stroke(self.cr, self.cg, self.cb);
    fill(255, 255, 255, 25);
    circle(self.x, self.y, radius*2);
    pop();
end


function setup() 
    createWindow(800, 600); 

    for i=1, ball_count do
      balls[i] = Ball:new(
            random(50, width-50),
            random(50, height-50),
            random(-100, 100),
            random(-100, 100)
        );
    end
    frameRate(60);
end

function draw()
    background('#461164');

    for i,ball in pairs(balls) do
        ball:draw();
        ball:move();
    end

    push();
    fill(255, 255, 255, 25);
    stroke(160, 90, 235)
    strokeWeight(3);
    circle(mouseX, mouseY, mouse_zone);
    pop();

    textSize(48);
    fill(100, 255, 10);
    text(round(frameRate()) .. ' fps', 30, 60);
end
