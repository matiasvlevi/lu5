local luax = require('site/lib/luax');

local Config = require('site/config');

local MethodCalls = require('site/components/MethodCalls');
local MethodExample = require('site/components/MethodExample');

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
        event=#props.doc.calls > 1 and props.doc.name .. '();' or get_declarations(props.doc)[1],
        method=#props.doc.calls > 1 and props.doc.name .. '();' or get_declarations(props.doc)[1],
        constant=props.doc.name,
        global=props.doc.name
    });

    local declarations;
    if (props.doc._type == "method") then
        declarations = get_declarations(props.doc);
    end

    -- Use branch master if dev, use version tag if prod
    local branch = 'master';
    if (Config.current_latest ==  VERSION) then
        branch = 'v' .. VERSION
    end

    -- Create github source permalink for method comment
    local doc_link = Config.metadata.github_url ..'/blob/' .. branch .. 
            '/src/bindings/' .. props.source.header .. 
            '#L' .. props.source.start_line .. 'C0-L'.. props.source.end_line .. 'C0';

    return luax('div', {class="method", id=props.doc.name}, {
        luax('div', {class="methodDeclaration"}, {
            luax('code', name),
            decorator
        }),
        luax('p', props.doc.description:len() > 0 and 
            props.doc.description or 
            'No description'
        ),
        MethodCalls({ declarations=declarations, method=props.doc }),
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
            luax.map(props.doc['examples'], function (ex, index) 
                return MethodExample(props.doc, ex, index)
            end),


        luax('span', {class="text small underline"}, luax('a', {target="_blank", href=doc_link}, 
            'See '.. props.doc.name .. ' in ' .. props.source.header
        ))
    })
end

return Method;