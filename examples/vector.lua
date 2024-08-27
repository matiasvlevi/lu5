
local a = createVector(3, 4);
local b = createVector(5, 6);


--- Non-Mutable

print('a: ', a, '+', b, '=', a + b);
print('a: ', a, '-', b, '=', a - b);
print('a: ', a, '*', b, '=', a * b);
print('a: ', a, '/', b, '=', a / b);


--- Mutable calls
print('Mutable Mult:')
print(a:mult(b)); -- vector
print(a:mult(5)); -- scalar
print(a:mult(5)); -- scalar
print(a:mult(5)); -- scalar

print('Mutable Add:')
print(a:add(b)); -- vector
print(a:add(5)); -- scalar

print('Mutable Sub:')
print(a:sub(createVector(1, 2))); -- vector
print(a:sub(2)); -- scalar

print('Mutable Div:')
print(a:div(createVector(4, 2))); -- vector
print(a:div(2)); -- scalar

print('Dot:')
print(a:dot(b)); -- vector
print(a:dot(5)); -- scalar


-- Distance
local distance = a:dist(b);
print('Distance between A and B: ', distance);

-- Swizzling
local e = createVector(1, 2, 3);
print('Vector Swizzling:')
print()
print(' vec     =', e    , '(original)');
print(' vec.xyz =', e.xyz, '(copy)');
print()
print(' vec.xzy =', e.xzy, '');
print(' vec.xxz =', e.xxz, '');
print(' vec.xxx =', e.xxx, '');
print(' vec.yzy =', e.yzy, '');
print(' vec.zxy =', e.zxy, '');
print(' vec.xzx =', e.xzx, '');