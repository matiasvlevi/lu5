
print();
print('--- LU5 PRINT EXAMPLE ---')
print('VERSION:', VERSION)
print();

print('Integers:')
print(1);
print(1, 2);
print(1, 2, 3);
print(1, 2, 3, 4);

print('Floats:')
print(1.);
print(1., 2.);
print(1., 2., 3.);
print(1., 2., 3., 4.);

print('Strings:')
print('Foo1');
print('Foo1', 'Foo2');
print('Foo1', 'Foo2', 'Foo3');

print('Tables:')
print({ 1, 2, 3 });
print({ 1, 2, 3 }, { 2, 3, 4 });
print({ 1, 2, 3 }, { 2, 3, 4 }, { 3, 4, 5 });

print('More tables:')
print({ 'Table', 'of', 'strings' });
print({ 'Table', 'of', 'more', 'strings' });


print();

local v = createVector(4, 5);
print('Vector:', v);

print()
print('Classes & instances')

local Ball = class('Ball');

function Ball:init(x, y)
    self.x = x;
    self.y = y;
    
    return self;
end


print(Ball)
print(Ball:new(260, 100))
print(Ball:new(200, 500))
print(Ball:new(275, 120))
print(Ball:new(100, 350))

print();
print('--- LU5 PRINT EXAMPLE END ---');
print();