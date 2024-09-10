local luax = require('site/lib/luax');

local Head = require('site/layout/Head');
local SocialButton = require('site/components/SocialButton');
---
-- @Component
-- @props TLayout {
--      purpose: string;
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
                slug=props.slug,
                parent=props.parent,
                version=props.version,
                purpose=props.purpose,
                page_name=props.page_name,
                meta=props.meta,
                media=props.media,
                ga=props.ga,
                scripts=props.scripts
            }),
            luax('body', {
                luax('div', {class="content flex flex-grow"}, {
                    ((props.nav ~= nil) and luax('div', {class="nav", id="menu"}, {
                        luax('br'),
                        props.nav 
                    }) or ''),
                    luax('main', {
                        luax('header', {
                            luax('div', {class='wrap'}, {
                                luax('a', {href=root == './' and props.meta.github_url or "../"}, {
                                    luax('img', {width="100px", src=root .. props.media.assets..'/logo.svg'}),
                                }),
                                luax('h1', {class="module", style=("font-size: ".. (props.purpose ~= "symbol" and "26pt" or  "22pt"))}, title),
            
                                (props.nav ~= nil) and luax('button', {class="menuBtn", onclick="toggleMenu()"}, {
                                    luax('img', {
                                        class="menuIcon", 
                                        width="40px", 
                                        src= root.. props.media.assets..'/arrow_left.svg'
                                    })
                                }) or '',
            
                                (props.version) and luax('span', {class="text version"}, {
                                    'v', VERSION
                                }) or ''
                            }),

                            luax('div', {class="space-between items-center gap-1 search-section", style="display: none;"}, {
                                luax('svg',{width="24px", height="24px", xmlns="http://www.w3.org/2000/svg", viewBox="0 0 50 50"}, {
                                    luax('path', {fill="currentColor", stroke="currentColor", d="M 21 3 C 11.601563 3 4 10.601563 4 20 C 4 29.398438 11.601563 37 21 37 C 24.355469 37 27.460938 36.015625 30.09375 34.34375 L 42.375 46.625 L 46.625 42.375 L 34.5 30.28125 C 36.679688 27.421875 38 23.878906 38 20 C 38 10.601563 30.398438 3 21 3 Z M 21 7 C 28.199219 7 34 12.800781 34 20 C 34 27.199219 28.199219 33 21 33 C 13.800781 33 8 27.199219 8 20 C 8 12.800781 13.800781 7 21 7 Z"}),
                                }),
                                luax('div', {class="search-wrap flex-col", style="position: relative;"}, {
    
                                    luax('input', {id="search", type="text",autocomplete="off", placeholder="Search", style="z-index: 5;"}, {}),
                                    luax('div', {class="search-box flex-col"}, {});
                                }),                    
                            }),

                        }),
                        children,
                    })
                }),
                luax('footer', {class="flex-col space-between"}, {
                    luax('div',{class="socials"}, {
                        SocialButton({
                            color="#fff",
                            icon= root .. props.media.assets .. "/github.svg",
                            link=props.meta.github_url,
                            label="matiasvlevi/lu5"
                        })
                    }),
                    luax('div', {class="license-note"}, {
                        luax('span',{class="smaller dark"}, 
                            'This project is licensed under the MIT License.'
                        ), luax('br'),
                        luax('span',{class="smaller dark"}, 
                            'It also includes the FreeType font engine, which is licensed under the FreeType License (FTL).'
                        )
                    })
                }),
            })
        });
    }) 
    
    
    

end

return Layout;