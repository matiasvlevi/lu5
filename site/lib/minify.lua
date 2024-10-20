
local fs = require("site/lib/file");

local function minify_css(css)
    -- Trim start/end whitespace
    css = css:match("^%s*(.-)%s*$")

    -- Append semicolons
    local processed_css = css:gsub("(%b{})", function(block)
        return block:gsub("([^;])(%s*})", "%1;}")
    end)

    css = processed_css;

    css = css:gsub("/%*.-%*/", "")
    css = css:gsub("%s*({)%s*", "%1"):gsub("%s*(})%s*", "%1")
    css = css:gsub("%s*(:)%s*", "%1"):gsub("%s*(;)%s*", "%1")
    css = css:gsub("%s*(,)%s*", "%1")
    css = css:gsub("\n", "")
    css = css:gsub(";}", "}")
    css = css:gsub("%s+", " ")
    return css
end

local function minify_js(js)
    js = js:gsub("//[^\n]*", "")
    js = js:gsub("/%*.-%*/", "")
    js = js:gsub("[ \t]+", " ")
    js = js:gsub("%s*({)%s*", "%1"):gsub("%s*(})%s*", "%1")
    js = js:gsub("%s*(;)%s*", "%1"):gsub("%s*(,)%s*", "%1")
    js = js:gsub("%s*(=)%s*", "%1")
    js = js:gsub("[\n]+", " ")
    js = js:gsub("%s+", " ")
    return js
end

local minifiers = {
    css=minify_css,
    js=minify_js
};

local mt = {};
return setmetatable(minifiers, mt)