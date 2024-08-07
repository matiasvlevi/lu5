local luax = require('tasks/lib/luax')

---
-- @Component
-- @props {
--      headers: string[];
--      class: string;
-- }
---
function HeaderPanel(props)
    return luax('ul', {
        luax.map(props.headers, function(header, key)
            -- Remove extention
            local header = luax.split(header, '.')[1];
            header = header:gsub('lu5%_', '');

            -- Create link to module page
            local link = './' .. header .. '/';

            return luax('li', {class="btn"}, {
                luax('a', {href=link, class=props.class}, {
                    luax('h4', header)
                })
            })
        end)
    })
end

return HeaderPanel