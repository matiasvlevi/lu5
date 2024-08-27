local global_assert_counter = 0;
local global_assert_fail_counter = 0;
local function _assert(cond, condstr, a, b, verbose)

    local iseq = cond(a, b);
    if (iseq) then
        global_assert_success_counter = global_assert_success_counter + 1;
    end

    global_assert_counter = global_assert_counter + 1;

    if (verbose == nil) then verbose = true; end
    if (verbose and not iseq) then 
        print('Assert failed (',global_assert_counter, '): ', a, condstr, b, '=', '\x1b[91mFailed\x1b[0m');

        local trace = debug.traceback();
        print(trace);
    end

    return iseq;
end

function assert(a, b, verbose) 
    _assert(function(a, b) 
        return a == b 
    end, '==', a, b, verbose);
end

function nassert(a, b, verbose) 
    _assert(function(a, b) 
        return a ~= b 
    end, '!=', a, b, verbose);
end


local function test(name, cb)
    if (cb == nil) then 
        cb = name;
        name = 'anonymous'
    end

    global_assert_counter = 0;
    global_assert_success_counter = 0;

    cb();

    print(name, 'tests passed:', global_assert_success_counter, '/', global_assert_counter);

    global_assert_counter = 0;
    global_assert_success_counter = 0;

    return assert(global_assert_counter, global_assert_success_counter, false);
end

return {
    test=test
}