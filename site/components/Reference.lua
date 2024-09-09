local luax = require('site/lib/luax')

local ModuleSummary = require('site/components/ModuleSummary')

local function Reference(props)
    return luax('div', {class="modules container", id="reactive"}, {
        luax.map(props.modules, function(mod, i)
            return ModuleSummary({
                title=mod.name,
                source=mod.source,
                methods=mod.methods
            })
        end)
    });
end

return Reference;