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

    return luax('div', {class="summary"}, {
        luax('h3', props.title),
        luax('ul', luax.map(props.methods, function(method, key)
            local link = './' .. props.title .. '.html#' .. method.name;

            return (method._type == "global") and '' or 
                luax('li', {class="index"}, {
                    luax('a', {href=link, class="index"}, {
                        method.name
                    })
                })
        end))
    });
end

return ModuleSummary