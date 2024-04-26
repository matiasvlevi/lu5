-- Links panel
local function Panel(headers)
    panel = '';

    for i, header in pairs(headers) do
        link = './' .. header .. '.html';

        panel = panel ..
            "<a href=\"".. link .."\">"..
                "<li class=\"btn\">"..
                    "<h4>" .. header .. "</h4>"..
                "</li>"..
            "</a>";
    end

    return "<ul>".. panel .."</ul>";
end

-- Exit link
local function ExitButton()
    return
        "<a href=\"./\" class=\"exitBtn\">"..
            "< Back"..
        "</a>" 
end

-- lu5 Method
local function Method(method)
    local params = '';

    -- Format all params
    for i, param in pairs(method.params) do
        params = params ..
            "<div class=\"param\">"                                       ..
                "<span class=\"name\">" .. param.name .. "</span>"        ..
                "<span class=\"desc\">" .. param.description .. "</span>" ..
            "</div>";
    end

    if (method.description == nil) then
        method.description = 'No description.';
    end

    return 
        "<div class=\"method\">"                        ..
            "<h3>"   .. method.name .. "</h3>"          ..
            "<p>"    .. method.description .. "</p>"    ..
            "<div class=\"params\">"                    .. 
                params                                  ..
            "</div>"                                    ..
            "<br/>"                                     ..
            "<code>" .. method.declaration .. "</code>" ..
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
	Panel=Panel,
	ExitButton=ExitButton
}