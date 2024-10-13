local luax = require('site/lib/luax');

function PictureMosaic(props)
    -- TODO: Take a list from props and map it to this:
    return luax('div', {class="mosaic"}, {
        luax('a', {target="_blank", href="https://github.com/matiasvlevi/lu5-space-game/"}, luax('img',{class="demo",
            height="266px",
            src=(props.root .. props.media.assets .. '/space_game.gif')
        })),
        luax('a', {target="_blank", href="https://github.com/matiasvlevi/lu5/blob/master/examples/sphere.lua"}, luax('img', {class="demo",
            height="133px", 
            src=(props.root .. props.media.assets .. '/sphere.gif')
        })),
        luax('a', {target="_blank", href="https://github.com/matiasvlevi/lu5/blob/master/examples/collisions.lua"}, luax('img',{class="demo",
            height="200px", 
            src=(props.root .. props.media.assets .. '/collisions.gif')
        })),

    })
end

return PictureMosaic;