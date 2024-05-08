-- Links panel
local function Panel(headers, class)
    local panel = '';

    for i, header in pairs(headers) do
        -- Remove extention
        local header = split(header, '.')[1];
        header = header:gsub('lu5%_', '');

        -- Create link to module page
        local link = './' .. header .. '.html';

        -- Panel
        panel = panel ..
            "<li class=\"btn\">"..
                "<a class=\"".. class .."\" href=\"".. link .."\">"..
                    "<h4>" .. header .. "</h4>"..
                "</a>"..
            "</li>";
    end

    return "<ul>".. panel .."</ul>";
end

local function MethodSummary(parent, methods, class)

    local summary = '';

    if (class == nil) then
        class = "dark"
    end

    for i, method in pairs(methods) do

        local link = './' .. parent .. '.html#' .. method.name;

        summary = summary .. "<li class=\"index\">"..
            "<a class=\"".. class .." index\" href=\"".. link .."\">"..
                method.name..
            "</a>"..
        "</li>";
    end

    return 
        "<div class=\"summary\">"..
            "<h3>".. parent .."</h3>"..
            "<ul>".. summary .."</ul>"..
        "</div>";
end

-- Links panel
local function Index(modules, class)
    local index = '';

    if (class == nil) then
        class = "dark"
    end

    for header, methods in pairs(modules) do

        -- Panel
        index = index .. MethodSummary(header, methods);
        
    end
    
    return 
        "<div class=\"modules\" id=\"reactive\">"..
            index..
        "</div>";
end


-- lu5 Method
local function Method(method)
    local params = '';

    -- Format all params
    for i, param in pairs(method.params) do
        params = params ..
            "<div class=\"param\">"                                       ..
                "<code class=\"name\">" .. param.name .. "</code>"        ..
                "<span class=\"text desc\">" .. param.description .. "</span>" ..
            "</div>";
    end

    if (method.description == nil) then
        method.description = 'No description.';
    end

    local returnContent = '';
    if (method['_return'] ~= nil) then
        returnContent = "<h4>Returns</h4><div class=\"param\">"                      ..
            "<code class=\"name\">" .. method['_return'].var .. "</code>" ..
            "<span class=\"text desc\">" .. method['_return'].description .. "</span>" ..
        "</div>"                                                     ;
    end

    local exampleContent = '';
    if (method['example'] ~= nil) then
        exampleContent = "<pre><code class=\"language-lua\">"..
            method['example'] ..
        "</code></pre>";
    end

    local decorator = '';
    if (method['is_event']) then
        decorator = '<span class="decorator">Event</span>';
    end

    return 
        "<div class=\"method\" id=\"".. method.name .. "\">" ..
            '<div class="methodDeclaration">'..
                "<code>" .. get_declaration(method) .. "</code>" ..
                decorator..
            '</div>'..
            "<p>"    .. method.description .. "</p>"         ..
            "<h4>Arguments</h4>"                             ..
            "<div class=\"params\">"                         .. 
                params                                       ..
            "</div>"                                         ..
            returnContent                                    ..
            "<p>"    .. method.bottom_description .. "</p>"  ..
            exampleContent                                   ..
            "<br/>"                                          ..
        "</div>" 
end

-- lu5 Module
local function Module(methods) 
    local content = ''

    for i, method in pairs(methods) do
        content = content .. '\n' .. 
            Method(method);
    end

    return content;
end

return {
	Module=Module,
    Index=Index,
	Method=Method,
	Panel=Panel
}
