
local a = createVector(3, 4);
local b = createVector(5, 6);

print('Mult:')
print(a:mult(b)); -- vector
print(a:mult(5)); -- scalar

print('Add:')
print(a:add(b)); -- vector
print(a:add(5)); -- scalar

print('Dot:')
print(a:dot(b)); -- vector
print(a:dot(5)); -- scalar

-- Distance
local distance = a:dist(b);

print('Distance between A and B: ', distance);

