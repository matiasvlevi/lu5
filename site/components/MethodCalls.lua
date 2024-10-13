local luax = require('site/lib/luax');

function MethodCall(props)
    return luax('', {
        props.declaration and luax('div', {class="methodDeclaration", style="margin-top: 2rem;-"}, {
            luax('code', props.declaration),
            decorator
        }) or '',
        #props.params > 0 and luax('h4', 'Arguments') or '',
        luax('div', {class="params"}, {
            luax.map(props.params, function(param, key)
                return luax('div', {class="param"}, {
                    luax('code', {class="name"}, param.name),
                    luax('span', {class="text desc"}, from_md(param.description))
                })
            end)
        })
    });
end

function MethodCalls(props)
    return luax('', {
        luax.map(props.method.calls, function(c, i)
            local dec = #props.method.calls > 1 and props.declarations[i] or nil;
            return luax('', {
                MethodCall({ declaration=dec, params=c.arguments }),
                c.example and MethodExample(props.method, c.example, i) or ''
            });
        end),
    });
end

return MethodCalls;