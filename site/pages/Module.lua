local luax = require('site/lib/luax')

local Method = require('site/components/Method')

---
-- @Component
-- @param props TMethod[];
---
function Module(props)
    return luax('', {
        luax.map(props.methods, function(method, i)
            return Method(method)
        end)
    })
end

return Module