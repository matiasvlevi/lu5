local Unit = require('tasks/lib/testing/assert')

Unit.test('Vector.add', function ()
    local const_a = createVector(3, 4);
    local const_b = createVector(5, 2);
    
    local a = createVector(3, 4);
    local b = createVector(5, 2);
        
    assert((a + b), createVector(8, 6));
    assert(const_a, a);
    assert(const_b, b);

    assert(Vector.add(a, b), createVector(8, 6));
    assert(const_a, a);
    assert(const_b, b);

    assert(a:add(b), createVector(8, 6));
    nassert(const_a, a);
    assert(const_b, b);

end)

Unit.test('Vector.mult', function ()
    local const_a = createVector(3, 4);
    local const_b = createVector(5, 2);
    
    local a = createVector(3, 4);
    local b = createVector(5, 2);
        
    assert((a * b), createVector(15, 8));
    assert(const_a, a);
    assert(const_b, b);

    assert(Vector.mult(a, b), createVector(15, 8));
    assert(const_a, a);
    assert(const_b, b);

    assert(a:mult(b), createVector(15, 8));
    nassert(const_a, a);
    assert(const_b, b);

end)

Unit.test('Vector.sub', function ()
    local const_a = createVector(3, 4);
    local const_b = createVector(5, 2);
    
    local a = createVector(3, 4);
    local b = createVector(5, 2);
        
    assert((a - b), createVector(-2, 2));
    assert(const_a, a);
    assert(const_b, b);

    assert(Vector.sub(a, b), createVector(-2, 2));
    assert(const_a, a);
    assert(const_b, b);

    assert(a:sub(b), createVector(-2, 2));
    nassert(const_a, a);
    assert(const_b, b);
end)

Unit.test('Vector.div', function ()
    local const_a = createVector(3, 4);
    local const_b = createVector(2, 2);
    
    local a = createVector(3, 4);
    local b = createVector(2, 2);
        
    assert((a / b), createVector(1.5, 2));
    assert(const_a, a);
    assert(const_b, b);

    assert(Vector.div(a, b), createVector(1.5, 2));
    assert(const_a, a);
    assert(const_b, b);

    assert(a:div(b), createVector(1.5, 2));
    nassert(const_a, a);
    assert(const_b, b);
end)

Unit.test('Vector.idiv', function ()
    local const_a = createVector(3, 4);
    local const_b = createVector(2, 2);
    
    local a = createVector(3, 4);
    local b = createVector(2, 2);
        
    assert((a // b), createVector(1, 2));
    assert(const_a, a);
    assert(const_b, b);

    assert(Vector.idiv(a, b), createVector(1, 2));
    assert(const_a, a);
    assert(const_b, b);

    assert(a:idiv(b), createVector(1, 2));
    nassert(const_a, a);
    assert(const_b, b);
end)

Unit.test('Vector.mag', function ()
    local a = createVector(3, 4);
        
    assert(Vector.magSq(a), 25);
    assert(Vector.mag(a), 5);

    assert(a:magSq(), 25);
    assert(a:mag(), 5);
end)

Unit.test('Vector.dist', function ()
    local a = createVector(2, 2);
    local b = createVector(-1, -2);
        
    assert(Vector.dist(a, b), 5);
    assert(a:dist(b), 5);

    local c = createVector(2, 2, 0);
    local d = createVector(-1, -2, 0);
        
    assert(Vector.dist(c, d), 5);
    assert(c:dist(d), 5);
end)


Unit.test('Vector.equals', function ()
    local a = createVector(2, 2, 3);
    local b = createVector(-1, -2, 1);
        
    assert(a == b, false);

    local c = createVector(2, 2, 3);
        
    assert(a == c, true);
end)


Unit.test('Vector.copy', function ()
    local a = createVector(7, 3, 4);
        
    -- same as a.xyz
    assert(a, a:copy());
end)

Unit.test('Vector Swizzling', function ()
    local a = createVector(1, 2, 3);
        
    -- Same as a:copy()
    assert(a.xyz, a);

    assert(a.yxz, createVector(2, 1, 3));
    assert(a.xxz, createVector(1, 1, 3));
    assert(a.zyx, createVector(3, 2, 1));

    assert(a.xy, createVector(1, 2));
    assert(a.xz, createVector(1, 3));
    assert(a.zz, createVector(3, 3));
end)

