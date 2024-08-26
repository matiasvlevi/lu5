
local obstacles = {};

local OBSTACLE_COUNT = 1000;

local ship;
local player;

local Player = require('examples/projects/space_game/Player');
local Obstacle = require('examples/projects/space_game/Obstacle');

function setup() 
  createWindow(800, 800, GL3D);

  player = Player:new(0, 0, 0);

  for i=1, OBSTACLE_COUNT do
      obstacles[i] = Obstacle:new(
        math.random(-800, 800), 
        math.random(-800, 800), 
        math.random(-15000, -500)
      );
  end
end

function draw()
  background(28, 10, 51);

  -- update player
  player:update();

  -- Update obstacles
  for i, obstacle in ipairs(obstacles) do
    if (obstacle:collides(player.pos.x, player.pos.y+200, 100)) then
      obstacle.color = { 255, 100, 10 };
      player.is_hit = true;
    else
      obstacle.color = { 100, 10, 155 };
    end

    obstacle:update(player.vel.z);
  end

  -- Render obstacles
  for i, obstacle in ipairs(obstacles) do
    obstacle:draw(player.pos.x, player.pos.y);
  end

  -- Render player
  player:draw();
end