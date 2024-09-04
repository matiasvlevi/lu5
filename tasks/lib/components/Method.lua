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
    local decorator = luax.match(props.doc._type, {
        event=luax('span', {class="decorator"}, 'Event'),
        constant=luax('span', {class="decorator"}, 'Constant'),
        global=luax('span', {class="decorator"}, 'Global')
    });


    local name = luax.match(props.doc._type, {
        event=#props.doc.calls > 1 and props.doc.name or get_declarations(props.doc)[1],
        method=#props.doc.calls > 1 and props.doc.name or get_declarations(props.doc)[1],
        constant=props.doc.name,
        global=props.doc.name
    });

    local declarations = luax.match(props.doc._type, {
        method=get_declarations(props.doc),
        default=nil
    });

    local branch = 'master';--'v' .. VERSION;
    local doc_link = 'https://github.com/matiasvlevi/lu5/blob/' .. branch.. 
            '/src/bindings/' .. props.source.header .. 
            '#L' .. props.source.start_line .. 'C0-L'.. props.source.end_line .. 'C0';

    return luax('div', {class="method",id=props.doc.name}, {
        luax('div', {class="methodDeclaration"}, {
            luax('code', name),
            decorator
        }),
        luax('p', props.doc.description:len() > 0 and 
            props.doc.description or 
            'No description'
        ),
        MethodCalls({ declarations=declarations, calls=props.doc.calls }),
        (props.doc['_return'] == nil) and '' or luax('', {
            luax('h4', 'Returns'),
            luax('div', {class="param"}, {
                luax('code', {class="name"}, {
                    props.doc['_return'].var
                }),
                luax('span', {class="text desc"}, {
                    props.doc['_return'].description
                })
            })
        }),
        luax('p', props.doc.bottom_description),

        (props.doc['examples'] == nil and #props.doc['examples'] <= 1) and '' or 
            luax.map(props.doc['examples'], MethodExample),


        -- luax('span', {class="text small underline"}, luax('a', {href=doc_link}, 
        --     'See '.. props.doc.name .. ' in ' .. props.source.header
        -- )),

        luax('br'),
    })
end

return Method;