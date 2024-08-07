local luax = require('tasks/lib/luax/luax')

local Method = require('tasks/lib/components/Method')

---
-- @Component
-- @props {
--      methods: TMethod[];
-- }
---
function Module(props) 
    return luax.map(props.methods, Method)
end

return Module