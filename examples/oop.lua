local Vector = class('Vector');

function Vector:init(x, y)
  self.x = x;
  self.y = y;
  return self;
end

function Vector:copy()
  return Vector:new(self.x, self.y);
end

function Vector:add(other)
  self.x = self.x + other.x;
  self.y = self.y + other.y;
end

function Vector:print()
  print(self.x, self.y);
end

local a = Vector:new(3, 4);
local b = Vector:new(5, 6);

a:print();
b:print();

local c = a:copy();
c:add(b);

c:print();
a:print();
