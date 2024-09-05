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
    local title = 'lu5 | ' .. props.page_name;
    local thumbnail = props.meta.url .. '/' .. props.media.assets .. '/' .. props.media.thumbnail;

    return luax('head', {
        luax('meta', {charset='UTF-8'}),
        luax('meta', {name='viewport', content='width=device-width, initial-scale=1.0'}),
        luax('meta', {httpEquiv='X-UA-Compatible', content='ie=edge'}),
    
        -- Basic
        luax('meta', {name='description', content=props.meta.description}),
        luax('meta', {name='keywords', content=luax.join(props.meta.keywords, ', ')}),
        luax('meta', {name='author', content=props.meta.author}),
    
        -- Open Graph
        luax('meta', {property='og:title', content=title}),
        luax('meta', {property='og:description', content=props.meta.description}),
        luax('meta', {property='og:image', content=thumbnail}),
        luax('meta', {property='og:url', content=props.meta.url}),
    
        -- Twitter card
        luax('meta', {name='twitter:card', content='summary_large_image'}),
        luax('meta', {name='twitter:title', content=title}),
        luax('meta', {name='twitter:description', content=props.meta.description}),
        luax('meta', {name='twitter:image', content=thumbnail}),

        props.root == './' and luax('link', {rel="prefetch", href=props.root .. props.media.assets .. '/space_game.gif'}) or '',
        props.root == './' and luax('link', {rel="prefetch", href=props.root .. props.media.assets .. '/collisions.gif'}) or '',
        props.root == './' and luax('link', {rel="prefetch", href=props.root .. props.media.assets .. '/sphere.gif'}) or '',

        -- Only index latest docs
        props.root == './' and '' or luax('link', {rel='canonical', href=props.meta.url .. '/latest/' }),
    
        -- CSS
        luax('link', {rel='stylesheet', href=props.root .. props.media.assets ..'/style.css'}),
        luax('link', {rel='stylesheet', href=props.root .. props.media.assets .. '/lu5-hljs-theme.css'}),

        -- JS
        luax('script', {src= props.root .. props.media.assets .. '/hljs.min.js'}, {}),
        luax('script', {type='text/javascript', src=props.root .. props.media.assets ..'/index.js'}, {}),
        --luax('script', {type='text/javascript', src=props.root .. props.media.assets ..'/lu5.js'}, {}),
        luax('script', {
            'document.addEventListener("DOMContentLoaded", function (event) {',
                'hljs.highlightAll();',
            '});'
        }),
        
        props.scripts and props.scripts or '',

        -- Google tag (gtag.js) --
        luax('script', {async=true, src="https://www.googletagmanager.com/gtag/js?id=" .. props.ga.gtag_id}, {}),
        luax('script', {
            'window.dataLayer = window.dataLayer || [];',
            'function gtag(){dataLayer.push(arguments);};',
            'gtag("js", new Date());',
            'gtag("config", "', props.ga.gtag_id ,'");'
        }),
        
        -- Icon & Title
        luax('link', {rel="icon", type="image/svg", href=props.root .. props.media.assets .. "/favicon.png"}),
        luax('title', title);
    })
end

return Head;