-- Links panel
local function Panel(headers)
    panel = '';

    for i, header in pairs(headers) do
        -- Remove extention
        header = split(header, '.')[1];

        -- Create link to module page
        link = './' .. header .. '.html';

        -- Panel
        panel = panel ..
            "<li class=\"btn\">"..
                "<a class=\"light\" href=\"".. link .."\">"..
                    "<h4>" .. header .. "</h4>"..
                "</a>"..
            "</li>";
    end

    return "<ul>".. panel .."</ul>";
end

-- lu5 Method
local function Method(method)
    local params = '';

    -- Format all params
    for i, param in pairs(method.params) do
        params = params ..
            "<div class=\"param\">"                                       ..
                "<code class=\"name\">" .. param.name .. "</code>"        ..
                "<span class=\"desc\">" .. param.description .. "</span>" ..
            "</div>";
    end

    if (method.description == nil) then
        method.description = 'No description.';
    end

    return 
        "<div class=\"method\">"                             ..

            "<code>" .. get_declaration(method) .. "</code>" ..
            "<p>"    .. method.description .. "</p>"         ..
            "<div class=\"params\">"                         .. 
                params                                       ..
            "</div>"                                         ..
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
	Method=Method,
	Panel=Panel
}
