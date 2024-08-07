
local fs = require("./tasks/lib/file");

function minify_css(css)
    css = css:gsub("/%*.-%*/", "")
    css = css:gsub("%s*({)%s*", "%1"):gsub("%s*(})%s*", "%1")
    css = css:gsub("%s*(:)%s*", "%1"):gsub("%s*(;)%s*", "%1")
    css = css:gsub("%s*(,)%s*", "%1")
    css = css:gsub("\n", "")
    css = css:gsub(";}", "}")
    css = css:gsub("%s+", " ")
    return css
end

function minify_js(js)
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
function mt.__call(t, files, minifier, source, dest)
    for i, filename in pairs(files) do
        local min = filename:find(".min.") == nil and minifier or function(s) return s end;
        fs.write_file(dest .. '/'.. filename, min(
            fs.read_file(source .. '/' .. filename)
        ));
    end
end

return setmetatable(minifiers, mt)