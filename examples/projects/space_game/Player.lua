
local Player = class('Player');
local Projectile = require('examples/projects/space_game/Projectile');
local ship = loadModel("examples/models/ship.obj");

local RELOAD_TIME = 0.1;

function Player:init(x, y, z)
  self.pos = createVector(x, y, z);
  self.vel = createVector(0, 0, 30);

  self.angle = createVector(0, 0, 0);
  self.angleVel = createVector(1, 0, 0);

  self.reloadTimer = 0;
  self.projectiles = {};

  self.is_hit = false;
  self.hit_timer = 0;

  return self;
end

function Player:shoot()
  table.insert(self.projectiles, 1, Projectile:new(
    self.pos.x, -- Pass player position
    self.pos.y - 12,
    440, 
    -self.vel.x/3, -- Pass player velocity
    -self.vel.y/3,
    self.vel.z
  ));
  self.reloadTimer = 0;
end

function Player:draw()
  push();
  
  translate(0, 200, 50);

  rotateY(90);
  rotateZ(self.angle.z);
  rotateX(180);
  rotateX(self.angle.x);

  scale(8);

  fill(230, 255, 100);
  stroke(195, 175, 10);
  strokeWeight(4);
  
  if (self.is_hit) then
    fill(255, 175, 100);
    self.angleVel.x = self.angleVel.x + random(-3, 3);
    self.angleVel.z = self.angleVel.z + random(-3, 3);
    if (self.hit_timer > (500 * deltaTime)) then
        self.is_hit = false;
        self.hit_timer = 0;
    end

    self.hit_timer = self.hit_timer +1

  end
  
  model(ship);

  pop();

  for i, proj in ipairs(self.projectiles) do
    proj:draw(self.pos.x, self.pos.y-100);
  end
end

function Player:update()
  -- Apply velocities
  self.pos.x = self.pos.x + self.vel.x;
  self.pos.y = self.pos.y + self.vel.y;

  -- Apply angle velocity
  self.angle.x = self.angle.x + self.angleVel.x;
  self.angle.z = self.angle.z + self.angleVel.z;

  -- Angle velocity friction
  self.angleVel.x = self.angleVel.x * 0.2;
  self.angleVel.z = self.angleVel.z * 0.2;

  -- Reset ship to initial angle 
  self.angle.x = self.angle.x * 0.8;
  self.angle.z = self.angle.z * 0.8;

  -- Left/Right
  if (keyIsDown('a')) then
    self.angleVel.x = self.angleVel.x + 6;
    self.vel.x = self.vel.x - 35*deltaTime;
  end
  if (keyIsDown('d')) then
    self.angleVel.x = self.angleVel.x - 6;
    self.vel.x = self.vel.x + 35*deltaTime;
  end

  -- Up/Down Pitch control
  if (keyIsDown('w')) then
    self.angleVel.z = self.angleVel.z - 4;
    self.vel.y = self.vel.y - 35*deltaTime;
  end
  if (keyIsDown('s')) then
    self.angleVel.z = self.angleVel.z + 4;
    self.vel.y = self.vel.y + 35*deltaTime;
  end



  if (self.vel.z < 60) then 
    self.vel.z = self.vel.z + 1*deltaTime
  end;

  self.vel.x = self.vel.x * 0.95; 
  self.vel.y = self.vel.y * 0.95;

  -- Shoot
  if (keyIsDown(32) and self.reloadTimer > RELOAD_TIME) then
    self:shoot();
  end
  self.reloadTimer = self.reloadTimer + 1*deltaTime;

  for i, proj in ipairs(self.projectiles) do
    proj:update();
  end
end

return Player