
local state = {};
state_current = 1;

function useState(initial)
    local state_c = state_current;
    state_current = state_current + 1;

    if (state[state_c] == nil) then
        state[state_c] = initial;
    end

    return function()
        return state[state_c] or 0;
    end, function (v)
        if type(v) == "function" then
            state[state_c] = v(state[state_c]);
        else
            state[state_c] = v;
        end
        luax_clear();
        state_current = 1;
        luax_createRoot('root', App());
    end
end

function App()
    local counter, setCounter = useState(0);
    local counter2, setCounter2 = useState(0);
    print(state, state_current)
    function handleClick(e)
        local n = counter() + 1;
        setCounter(n)
    end
    function handleClick2(e)
        local n = counter2() + 1;
        setCounter2(n)
    end
    return luax('main', {
        luax('h1', 'useState in lu5'),
        luax('button', {onclick=handleClick}, {
            'Clicked:' .. counter(),
        }),
        luax('button', {onclick=handleClick2}, {
            'Clicked2:' .. counter2(),
        }),

    })
end

function App2()
    local counter, setCounter = useState(0);
    local counter2, setCounter2 = useState(0);
    print(state, state_current)
    function handleClick(e)
        local n = counter() + 1;
        setCounter(n)
    end
    function handleClick2(e)
        local n = counter2() + 1;
        setCounter2(n)
    end
    return luax('main', {
        luax('h1', 'useState in lu5'),
        luax('button', {onclick=handleClick}, {
            'Clicked:' .. counter(),
        }),
        luax('button', {onclick=handleClick2}, {
            'Clicked2:' .. counter2(),
        }),

    })
end

luax_createRoot('root', App());
luax_createRoot('root2', App2());
print(events)