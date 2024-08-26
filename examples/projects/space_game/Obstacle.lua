
local Obstacle = class('Obstacle')

function Obstacle:init(x, y, z)
    self.x = x;
    self.y = y;
    self.z = z;
    self.color = { 100, 10, 155 };
    self.angle = random(0, 360);
    self.size = (random(0, 1) > 0.3) and random(10, 24) or 64;
    return self;
end

function Obstacle:update(speed)
    self.angle = self.angle + 0.04;
    self.z = self.z + speed; 
    if (self.z > 800) then
        self.x = math.random(-800, 800);
        self.y = math.random(-800, 800);
        self.z = math.random(-25000, -15000)
    end
end

function Obstacle:draw(offsetx, offsety)
    push();
    strokeWeight(4);
    stroke(60, 0, 110);
    fill(self.color[1], self.color[2], self.color[3]);
    translate(-offsetx + self.x, -offsety + self.y, self.z);
    rotateX(self.angle);
    rotateZ(2*self.angle);
    box(self.size);
    pop();
end

function Obstacle:collides(x, y ,z)

  if (self.z < 100) then return false end;
  local distance = dist(self.x, self.y, self.z, x, y , z);
  local collision = (distance < self.size and self.size > 10);

  return collision; 
end

function Obstacle:print()
    print(self.x, self.y, self.z, self.angle);
end

return Obstacle