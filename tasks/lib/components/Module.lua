local luax = require('tasks/lib/luax')

local Method = require('tasks/lib/components/Method')

---
-- @Component
-- @props {
--      methods: TMethod[];
-- }
---
function Module(props)
    return luax('', {
        luax.map(props.methods, function(method, i)
            return Method(method)
        end)
    })
end

return Module