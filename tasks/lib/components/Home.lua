local luax = require('tasks/lib/luax/luax')

local ModuleSummary = require('tasks/lib/components/ModuleSummary')

local function Home(props)    
    return luax('div', {class="modules", id="reactive"}, {
        luax.map(props.modules, function(methods, moduleName)
            return ModuleSummary({
                title=moduleName,
                methods=methods
            })
        end),
    });
end

return Home;