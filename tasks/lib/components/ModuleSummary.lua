local luax = require('tasks/lib/luax');

---
-- @Component
-- @props {
--      title: string;
--      methods: TMethod[];
-- }
---
function ModuleSummary(props)
    -- Avoid showing empty modules
    if (#props.methods == 0) then
        return '';
    end

    local title = props.title:gsub('%_', ' ');

    return luax('div', {class="summary"}, {
        luax('h3', title),
        luax('ul', luax.map(props.methods, function(method, key)
            local link = './' .. props.source .. '/#' .. method.name;

            return (method._type == "constant") and '' or 
                luax('li', {class="index"}, {
                    luax('a', {href=link, class="index"}, {
                        method.name
                    })
                })
        end))
    });
end

return ModuleSummary