local luax = require('site/lib/luax');
local Config = require('site/config');

---
-- @Component
-- @props THead {
--      purpose: string;
--      page_name: string;
--      media: TMedia;
--      meta: TMetadata;
-- }
---
function Head(props)
    local title = props.page_name;
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

        -- CSS
        luax('link', {rel='stylesheet', href=props.root .. props.media.assets ..'/common.css'}),

        (props.purpose ~= "editor") and (
            luax('link', {rel='stylesheet', href=props.root .. props.media.assets ..'/docs.css'})
        ) or '',

        (props.purpose == "reference") and luax('', {
            -- Only index latest docs
            luax('link', {rel='canonical', href=props.meta.url .. '/latest/' })
        }) or '',

        (props.purpose == "reference" or 
         props.purpose == "symbol" or
         props.purpose == "module" 
        ) and luax('', {
            -- Search
            luax('script', {type='text/javascript', src=props.root .. props.media.assets ..'/search.js'}, {}),
            
            -- Menu
            luax('script', {type='text/javascript', src=props.root .. props.media.assets ..'/menu.js'}, {}),
            luax('script', {
                'window.onload = function (e) {',
                    'set_nav_menu();',
                    'set_search("', props.root ,'v', VERSION ,'/");',
                '};'
            })
        }) or '';

        props.purpose == "homepage" and luax('', {
            -- highlight.js language-html
            luax('script', {src="https://unpkg.com/@highlightjs/cdn-assets@11.9.0/languages/html.min.js"}),

            -- gifs
            luax('link', {rel="prefetch", href=props.root .. props.media.assets .. '/space_game.gif'}),
            luax('link', {rel="prefetch", href=props.root .. props.media.assets .. '/collisions.gif'}),
            luax('link', {rel="prefetch", href=props.root .. props.media.assets .. '/sphere.gif'}),        

            -- Resize images
            luax('script', {type='text/javascript', src=props.root .. props.media.assets ..'/image.js'}, {}),
            
            -- Set right download interface
            luax('script', {type='text/javascript', src=props.root .. props.media.assets ..'/download.js'}, {}),
            
            luax('script', {
                'window.onload = function (e) {',
                    'set_image_size();',
                    'set_download_frontend();',
                '};'
            })
        }) or '',

        (props.purpose == "homepage" or
         props.purpose == "module" or
         props.purpose == "symbol" or
         props.purpose == "editor"
        ) and luax('', {
            -- Highlight.js theme
            (props.purpose == "editor") and luax('', {
                -- luax('link', {rel='stylesheet', href=props.root .. props.media.assets .. '/editor.css'})
            }) or (
                luax('link', {rel='stylesheet', href=props.root .. props.media.assets .. '/lu5-hljs-theme.css'})
            ),
            
            luax('script', {src="https://unpkg.com/@highlightjs/cdn-assets@11.9.0/highlight.min.js"}, {}),

            luax('script', {
                'document.addEventListener("DOMContentLoaded", function (e) {',
                    'hljs.configure({ noHighlightRe: /^no-hljs$/i });',
                    'hljs.highlightAll();',
                '});'
            }),

        }) or '',

        (props.purpose == "module" or 
         props.purpose == "symbol" or
         props.purpose == "editor"
        ) and luax('', {
            -- highlight.js language-lua
            luax('script', {src="https://unpkg.com/@highlightjs/cdn-assets@11.9.0/languages/lua.min.js"}),


            (props.purpose == "editor") and (luax('', {
                luax('script', { type="module", src=Config.cdn.lu5_editor, defer=true }),
                -- luax('script', { src="https://codemirror.net/1/contrib/lua/js/parselua.js" })
            })) or (luax('', {
                -- lu5-wasm
                luax('script', { type="module", src=Config.cdn.lu5_wasm }),
                luax('script', { type="module", src=Config.cdn.lu5_console }),
            })),
        }) or '',

        (props.purpose == "symbol") and luax('', {
            luax('link', {rel='canonical', href=props.meta.url .. '/latest/' .. props.parent .. '/' .. props.slug }),
        }) or '',

        (props.purpose == "module") and luax('', {
            luax('link', {rel='canonical', href=props.meta.url .. '/latest/' .. props.slug }),
        }) or '',

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