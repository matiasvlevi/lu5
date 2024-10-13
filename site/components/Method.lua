local luax = require('site/lib/luax');

local Config = require('site/config');

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

function MethodCalls(props, root)
    return luax('', {
        luax.map(props.method.calls, function(c, i)
            local dec = #props.method.calls > 1 and props.declarations[i] or nil;
            return luax('', {
                MethodCall({ declaration=dec, params=c.arguments }),
                c.example and MethodExample(props.method, c.example, i, root) or ''
            });
        end),
    });
end

function MethodExample(method, example, index, root)
    return example.source ~= nil and luax('div', {class="method-example flex items-center"}, {
        luax('pre', {class="example-code"},{
            luax('code', {class="language-lua"}, { example.source })
        }),
        example.live and LiveCanvas(root, method.name, index, example.source) or '',
    }) or ''
end

function LiveCanvas(root, name, index, source)
    return luax('', {
        luax('canvas', { id="example-visual-"..name.."-"..index, style="display:none;" }),
        luax('div', {class="flex-col", style="margin: 1.5rem 0;"}, {
            luax('div', { id="example_"..name .."_"..index.."_console", style="min-width: 22rem; max-height: 16rem;"}, {
                luax('p', {class="text white monospace underline", style="margin: 0.2rem 0 0.6rem 0;"}, 'Output')
            }),
        }),
        luax('script', {
            'const example_', name, '_', index,'_console = new lu5.Console(`example_',name,'_',index,'_console`);',
            'lu5.init()',
                '.then(vm => vm.setCanvas("example-visual-', name, '-', index ,'"))',
                '.then(vm => vm.attach(1, example_', name, '_', index,'_console))',
                '.then(vm => vm.attach(2, example_', name, '_', index,'_console))',
                '.then(vm => vm.attach(2, console))',
                '.then(vm => vm.execute(`', source ,' \n`));',
        });
    })
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
function Method(props, root)
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
        MethodCalls({ declarations=declarations, method=props.doc }, root),
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
                return MethodExample(props.doc, ex, index, root)
            end),


        luax('span', {class="text small underline"}, luax('a', {target="_blank", href=doc_link}, 
            'See '.. props.doc.name .. ' in ' .. props.source.header
        ))
    })
end

return Method;