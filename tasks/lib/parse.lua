function split(input, sep)
    local content={}
    for str in string.gmatch(input, "([^"..sep.."]+)") do
        table.insert(content, str);
    end
    return content
end

function join(list, sep)
    if (#list < 1) then 
        return '';
    end

    local str = list[1];

    if (#list == 1) then
        return str;
    end

    for i=2,#list do
        str = str .. sep .. list[i];
    end

    return str;
end

function insert(str1, str2, pos)
    return str1:sub(1,pos-1)..str2..str1:sub(pos+1)
end

function from_md(text)
    local in_scope = true;

    local i = 1;

    local ans = text;
    local len = #text;

    while (ans:find('`') ~= nil and i <= len) do
        if (string.sub(ans, i, i) == '`') then
            local added = '';
            if (in_scope) then
                added = '<code class="inline">';
                ans = insert(ans, added, i);
            else
                added = '</code>'
                ans = insert(ans, added, i);

            end
            in_scope = not in_scope;

            i = i + #added;
            len = #ans
        end
        i = i + 1;
    end

    return ans;
end

function parse_param(param)
    local words = split(param, ' ');

    -- param
    --  name: string
    --  description: string
    local param = {};

    -- Remove param tag
    table.remove(words, 1);

    -- first element is name
    param['name'] = words[1];

    if (#words < 2) then
        param['description'] = 'No description.';
    else
        -- Remove name, and join array
        table.remove(words, 1);
        param['description'] = join(words, ' ');
    end

    return param;
end

function parse_description(comment)
	local lines = split(comment, '\n');
	local result = {};
	for i=1, #lines do
		-- filter only text
        local tagmatch = string.match(lines[i], "%@%w+");
        if (tagmatch ~= nil) then
            -- Allow brief
            if (string.match(tagmatch, '%@example') ~= nil) then
                -- End of description
                break;
            end
            if (string.match(tagmatch, '%@param') ~= nil) then
                -- End of description
                break;
            end
            goto continue;
        end
        
        local m = string.match(lines[i], "%s%*%s.+");
        if (m ~= nil) then
            table.insert(result, 1, from_md(string.sub(m, 4, #m)));
        end
    
        ::continue::
	end
	return join(result, '\n');
end

function parse_bottom_description(comment)
    if (comment:find('%@param') == nil) then 
        return ''; 
    end;

	local lines = split(comment, '\n');
	local result = {};
    
    local ignore = false;

	for i=#lines, 1, -1  do
        -- If encounter example, toggle ignore flag
        local examplematch = string.match(lines[i], "%@example");
        if (examplematch ~= nil) then
            -- Skip first example tag (seen 2nd in the iteration)
            if (ignore) then
                i = i - 1;
            end

            ignore = not ignore;
        end

        -- Add bottom description line
        if (not ignore) then
            -- if encounter a param, return bottom description
            local tagmatch = string.match(lines[i], "%@");
            if (tagmatch ~= nil) then
                return join(result, '\n');
            end

            local m = string.match(lines[i], "%s%*%s.+");
            if (m ~= nil) then
                table.insert(result, 1,  from_md(string.sub(m, 4, #m)) );
            end
        end

	end
	return '';
end

function parse_return(comment)
	local lines = split(comment, '\n');

	for i=1, #lines do
		-- filter only text
        local m = string.match(comment, "@return%s[%w ,.?!]+");
		if (m ~= nil) then
            local ws = split(m, ' ');
            local var = ws[2];
            table.remove(ws, 1);
            table.remove(ws, 1);

			-- TReturn
			-- var: string
			-- description: string
			--
            return {
                var=var,
                description=join(ws, ' ')
            };
        end
	end

	return nil;
end

function parse_example(comment)
	local lines = split(comment, '\n');
	local result = {};

    local i = 1;

    -- Skip to first example
    while (string.find(lines[i], '@example') == nil and i < #lines) do
        i = i + 1;
    end

    -- Skip example tag
    i = i + 1;

    -- Iterate through example and collect lines
    if (i < #lines) then
        while (string.find(lines[i], '@example') == nil and i < #lines) do

            local str = lines[i]:gsub('%s-%*%s-', '');

            table.insert(result, str);
            i = i + 1;
        end
    end

    if (#result < 1) then
        return nil;
    end
	return join(result, '\n');
end

function parse_comment(comment, name, is_event)

    local _type = '';
    if (comment:find('%@global')) then
        _type = 'global';
    elseif (comment:find('%@event') or is_event) then
        _type = 'event';
    else
        _type = 'method';
    end
    
    return {
		name              =name,
        _type             =_type,
		description       =parse_description(comment),
		example           =parse_example(comment),
		bottom_description=parse_bottom_description(comment),
		params            =parse_params(comment),
		_return           =parse_return(comment)
	};
end

function parse_params(comment)
	local params = {};
    local matches = string.gmatch(comment, "@param .- [%w ,.?!%`%_]+");
    
    local index = 1;
    for match in matches do   
        params[index] = parse_param(match);
        index = index + 1;
    end

	return params;
end

function parse_header(source)
    local function_comments = string.gmatch(source, "%/%*%*.-%*%/%s-%\nint .-%(.-%)");
    local callback_comments = string.gmatch(source, "%/%*%*%\n%s%*%s%@brief.-%*%/");
    -- methods: method[]
    local methods = {};

    local index = 1;
    for comment in function_comments do

        -- Get declaration and name
        local lines = split(comment, '\n');

        -- TODO: Add error handling for nil values to enhance DX
        local dec = string.match(lines[#lines], 'int .-%(.*%)'):gsub('lu5_', '') .. ';';
        local name = split(split(dec, ' ')[2], '(')[1];

        methods[index] = parse_comment(comment, name, false, false);
        index = index + 1;
    end

    for comment in callback_comments do
        -- TODO: Add error handling for nil values to enhance DX
        local name = split(string.match(comment, '@brief.-%\n'), ' ')[2]:sub(1, -2);
        methods[index] = parse_comment(comment, name, true, false);
        index = index + 1;
    end

    return methods;

end

function get_declaration(method)
    local args = {};

    -- Get all parameter names
    for i, param in pairs(method.params) do
        args[i] = param.name;
    end

    -- Replace lua_State argument with actual lua arguments 
    return (
        method.name .. '(' .. join(args, ', ') .. ');'
    )
end

return {
	description=parse_description,
	header=parse_header,
	param=parse_param,
	comment=parse_comment,
    get_declaration=get_declaration
}
