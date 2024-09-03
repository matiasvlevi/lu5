local luax = require('tasks/lib/luax');

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
        luax.map(props.calls, function(c, i)
            local dec = #props.calls > 1 and props.declarations[i] or nil;
            return luax('', {
                MethodCall({ declaration=dec, params=c.arguments }),
                c.example and MethodExample(c.example) or ''
            });
        end),
    });
end

function MethodExample(example) 
    return example ~= nil and luax('pre', {
        luax('code', {class="language-lua"}, { example })
    }) or ''
end

---
-- @Component
-- @props TMethod {
--      _type: string;
--      name: string;
--      description: string;
--      example: string;
--      bottom_description: string;
--      params: TParam[];
--      calls: TParam[][];
--      _return: TRetrun;
-- }
---
function Method(props)
    local decorator = luax.match(props._type, {
        event=luax('span', {class="decorator"}, 'Event'),
        constant=luax('span', {class="decorator"}, 'Constant'),
        global=luax('span', {class="decorator"}, 'Global')
    });


    local name = luax.match(props._type, {
        event=#props.calls > 1 and props.name or get_declarations(props)[1],
        method=#props.calls > 1 and props.name or get_declarations(props)[1],
        constant=props.name,
        global=props.name
    });

    local declarations = luax.match(props._type, {
        method=get_declarations(props),
        default=nil
    });

    return luax('div', {class="method",id=props.name}, {
        luax('div', {class="methodDeclaration"}, {
            luax('code', name),
            decorator
        }),
        luax('p', props.description:len() > 0 and 
            props.description or 
            'No description'
        ),
        MethodCalls({ declarations=declarations, calls=props.calls }),
        (props['_return'] == nil) and '' or luax('', {
            luax('h4', 'Returns'),
            luax('div', {class="param"}, {
                luax('code', {class="name"}, {
                    props['_return'].var
                }),
                luax('span', {class="text desc"}, {
                    props['_return'].description
                })
            })
        }),
        luax('p', props.bottom_description),

        (props['examples'] == nil and #props['examples'] <= 1) and '' or 
            luax.map(props['examples'], MethodExample),

        luax('br'),
    })
end

return Method;