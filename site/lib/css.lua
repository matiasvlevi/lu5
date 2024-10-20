local luax = require('site/lib/luax');
local Minify = require('site/lib/minify');
local fs = require('site/lib/file');

--- 
-- Add Higher level JS/CSS utilities
---

function import(path)
    return fs.read_file(path);
end

-- Add css dynamically
function luax.css(css_sources)
    local cssText = '';
    for i, source in ipairs(css_sources) do
        cssText = cssText .. Minify.css(source);
    end

    return luax('script', {'(()=>{',
        'const cssText = `', cssText ,'`;',
        'const style = document.createElement("style");',
        'style.type="text/css";',
        'if(style.styleSheet){',
            'style.styleSheet.cssText=cssText;',
        '}else{',
            'style.appendChild(document.createTextNode(cssText));',
        '}',
        'document.getElementsByTagName("head")[0].appendChild(style);',
    '})();'})
end