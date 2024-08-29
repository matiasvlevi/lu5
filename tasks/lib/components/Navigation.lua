local luax = require('tasks/lib/luax')

---
-- @Component
-- @props {
--      modules: {
--          name: string,
--          source: string,
--          methods: TMethod[];
--      }
--      class: string;
-- }
---
function Navigation(props)

    return luax('ul', {
        luax.map(props.modules, function(mod, key)
            -- Remove extention
            local header = luax.split(mod.source, '.')[1];
            header = header:gsub('lu5%_', '');

            -- Create link to module page
            local link = './' .. header .. '/';

            return luax('li', {class="btn"}, {
                luax('a', {href=link, class=(props.class and props.class or '')}, {
                    luax('h4', mod.name)
                })
            })
        end)
    })
end

return HeaderPanel