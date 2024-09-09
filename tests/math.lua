local Unit = require('tests/lib/assert')

Unit.test('dist', function ()
    assert(dist(2, 2, -1, -2), 5);
end)

Unit.test('max', function ()
    assert(max(2, 2, -1, -2), 2);
    assert(max(2, 215, -100, -2), 215);
    assert(max(89, 45, 2), 89);
    assert(max(1, 2), 2);
    assert(max({ 1 }), 1);
    assert(max({ 20, 300, -100, -2 }), 300);
end)

Unit.test('min', function ()
    assert(min(2, 2, -1, -2), -2);
    assert(min(2, 215, -100, -2), -100);
    assert(min(89, 45, 2), 2);
    assert(min({ 3 }), 3);
    assert(min({ 20, 300, -100, -2 }), -100);
end)

Unit.test('random', function ()
    for i=1, 20, 1 do
        local ran = random(5, 10);
        if (ran < 5 or ran > 10) then
            assert(false, true);
        else
            assert(ran, ran);
        end
    end
end)
