local luax = require('tasks/lib/luax');

---
-- @Component
-- @props THead {
--      page_name: string;
--      media: TMedia;
--      meta: TMetadata;
-- }
---
function Head(props)
    local title = props.page_name .. ' | ' .. props.meta.title;
    local thumbnail = '../' .. props.media.assets ..'/' .. props.media.thumbnail;

    return luax('head', {
        luax('meta', {charset='UTF-8'}),
        luax('meta', {name='viewport', content='width=device-width, initial-scale=1.0'}),
        luax('meta', {httpEquiv='X-UA-Compatible', content='ie=edge'}),
    
        -- Basic
        luax('meta', {name='description', content=props.meta.description}),
        luax('meta', {name='keywords', content=luax.join(props.meta.keywords, ', ')}),
        luax('meta', {name='author', content=props.meta.author}),
    
        -- Facebook card
        luax('meta', {property='og:title', content=title}),
        luax('meta', {property='og:description', content=props.meta.description}),
        luax('meta', {property='og:image', content=thumbnail}),
        luax('meta', {property='og:url', content=props.meta.url}),
    
        -- Twitter card
        luax('meta', {name='twitter:card', content='summary_large_image'}),
        luax('meta', {name='twitter:title', content=title}),
        luax('meta', {name='twitter:description', content=props.meta.description}),
        luax('meta', {name='twitter:image', content=thumbnail}),

        -- Only index latest docs
        luax('link', {rel='canonical', href=props.meta.url .. '/latest/' }),
    
        -- CSS
        luax('link', {rel='stylesheet', href='../' .. props.media.assets ..'/style.css'}),
        luax('link', {rel='stylesheet', href='../' .. props.media.assets .. '/lu5-hljs-theme.css'}),

        -- JS
        luax('script', {src= '../' .. props.media.assets .. '/hljs.min.js'}, {}),
        luax('script', {type='text/javascript', src='../' .. props.media.assets ..'/index.js'}, {}),
        luax('script', {
            'document.addEventListener("DOMContentLoaded", function (event) {',
                'hljs.highlightAll();',
                'main();',
            '})'
        }),
    
        luax('title', title)
    })
end

return Head;