local Projectile = class('Projectile');

function Projectile:init(x, y, z, vx, vy, vz)
  self.x = x;
  self.y = y;
  self.z = z;

  self.vx = vx;
  self.vy = vy;
  self.vz = vz;

  return self;
end

function Projectile:update()
  self.z = self.z - 50 - self.vz;
  self.y = self.y + self.vy
  self.x = self.x + self.vx
end

function Projectile:draw(offsetx, offsety)
  push();
  translate(-offsetx + self.x, -offsety + self.y, self.z + 12);
  fill(255, 210, 100);
  noStroke();
  box(1, 6);
  pop();
end

return Projectile