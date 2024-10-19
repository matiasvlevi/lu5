
local luax = require('site/lib/luax')


function Menuitem(props)
    return luax('li', {
        luax('a', {href="#"}, props.label),
        luax('ul', {
            luax.map(props.options, function (option)
                return luax('li', {
                    luax('a', {href="#"}, option.label)
                })
            end)
        })
    })
end

function Menubar(props)
    return luax('ul', {class="drop-menu"}, {
        luax.map(props.buttons, function (button) 
            return Menuitem(button)
        end)
    })
end

return Menubar;