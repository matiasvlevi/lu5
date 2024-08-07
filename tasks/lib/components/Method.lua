local luax = require('tasks/lib/luax');


---
-- @Component
-- @props TMethod {
--      _type: string;
--      name: string;
--      description: string;
--      example: string;
--      bottom_description: string;
--      params: TParam[];
--      _return: TRetrun;
-- }
---
function Method(props)
    local decorator = luax.match(props._type, {
        event=luax('span', {class="decorator"}, 'Event'),
        global=luax('span', {class="decorator"}, 'Global')
    });

    local name = luax.match(props._type, {
        event=get_declaration(props),
        method=get_declaration(props),
        global=props.name
    })

    return luax('div', {class="method",id=props.name}, {
        luax('div', {class="methodDeclaration"}, {
            luax('code', name),
            decorator
        }),
        luax('p', props.description:len() > 0 and 
            props.description or 
            'No description'
        ),
        (#props.params == 0) and '' or luax('', {
            luax('h4', 'Arguments'),
            luax('div', {class="params"}, {
                luax.map(props.params, function(param, key)
                    return luax('div', {class="param"}, {
                        luax('code', {class="name"}, param.name),
                        luax('span', {class="text desc"}, from_md(param.description))
                    })
                end)
            })
        }),
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
        (props['example'] == nil) and '' or luax('pre', {
            luax('code', {class="language-lua"}, {
                props['example']
            })
        }),
        luax('br'),
    })
end

return Method;