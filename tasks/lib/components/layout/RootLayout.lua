local luax = require('tasks/lib/luax/luax');

local Head = require('tasks/lib/components/layout/Head');
local Panel = require('tasks/lib/components/Panel');

---
-- @Component
-- @props TLayout {
--      page_name: string;
--      media: TMedia;
--      meta: TMetadata;
--      headers: string[];
--      children: string
-- }
---
function Layout(props)
    return luax('html', {lang="en"}, {
        Head({
            page_name=props.page_name,
            meta=props.meta,
            media=props.media
        }),
        luax('body', {
            luax('div', {class="nav", id="menu"}, {
                luax('br'),
                Panel({ class="light", headers=props.headers })
            }),
            luax('main', {
                luax('header', {
                    luax('a', {href="./"}, {
                        luax('img', {width="100px", src=props.media.assets..'/logo.svg'}),
                    }),
                    luax('h1', {class="module"}, props.page_name),
                    luax('button', {class="menuBtn", onclick="toggleMenu()"}, {
                        luax('img', {
                            class="menuIcon", 
                            width="40px", 
                            src=props.media.assets..'/arrow_left.svg'
                        })
                    }),
                    luax('span', {class="text version"}, VERSION)
                }),
                props.children
            })
        })
    });
end

return Layout;