local luax = require('tasks/lib/luax')

---
-- @Component
-- @props {
--      headers: string[];
--      class: string;
-- }
---
function Panel(props)
    return luax('ul', {
        luax.map(props.elements, function(element, key)
            return luax('li', { class="btn light" }, {
                (element.href == nil) and 
                    luax('h4', element.label)
                or 
                    luax('a', {href=element.href, class="light"}, {
                        luax('h4', element.label)
                    })
            })
        end)
    })
end

return Panel