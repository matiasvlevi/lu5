local luax = require('tasks/lib/luax');

local Head = require('tasks/lib/components/layout/Head');
---
-- @Component
-- @props TLayout {
--      page_name: string;
--      media: TMedia;
--      meta: TMetadata;
--      nav: string;
--      children: string;
-- }
---
function Layout(props, children)
    local root = (props.root ~= nil) and props.root or './';

    local title = props.page_name;

    return luax('', {
        '<!DOCTYPE html>',
        luax('html', {lang="en"}, {
            Head({
                root=root,
                page_name=props.page_name,
                meta=props.meta,
                media=props.media,
                ga=props.ga,
                scripts=props.scripts
            }),
            luax('body', {
                ((props.nav ~= nil) and luax('div', {class="nav", id="menu"}, {
                    luax('br'),
                    props.nav 
                }) or ''),
                luax('main', {
                    luax('header', {
                        luax('a', {href="../"}, {
                            luax('img', {width="100px", src=root .. props.media.assets..'/logo.svg'}),
                        }),
                        luax('h1', {class="module"}, title),
    
                        ((props.nav ~= nil) and luax('button', {class="menuBtn", onclick="toggleMenu()"}, {
                            luax('img', {
                                class="menuIcon", 
                                width="40px", 
                                src= root.. props.media.assets..'/arrow_left.svg'
                            })
                        }) or ''),
    
                        (props.version) and luax('span', {class="text version"}, {
                            'v', VERSION
                        }) or ''
                    }),
                    children
                })
            })
        });
    }) 
    
    
    

end

return Layout;