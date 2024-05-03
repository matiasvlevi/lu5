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
        local tagmatch = string.match(lines[i], "%@");
        if (tagmatch ~= nil) then
            break;
        end

		local m = string.match(lines[i], "%s%*%s.+");
		if (m ~= nil) then
			table.insert(result, 1, string.sub(m, 4, #m));
		end
	end
	return join(result, '\n');
end

function parse_bottom_description(comment)
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
                table.insert(result, 1,  string.sub(m, 4, #m) );
            end
        end

	end
	return '';
end

function parse_return(comment)
	local lines = split(comment, '\n');
	local result = {};
	for i=1, #lines do
		-- filter only text
        local m = string.match(comment, "@return%s[%w ,.?!]+");
		if (m ~= nil) then
            local ws = split(m, ' ');
            local var = ws[2];
            table.remove(ws, 1);
            table.remove(ws, 1);

            return {
                var=var,
                description=join(ws, ' ')
            };
        end
	end

	return result[0];
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

function parse_comment(comment)

    local matches = string.gmatch(comment, "@param .- .-%\n");

    -- method
    --  name: string
    --  declaration: string
    --  params: param[]
    local method = {};

    local lines = split(comment, '\n');

    local dec = string.match(lines[#lines], 'int .-%(.*%)') .. ';';

    dec = dec:gsub('lu5_', '');

    method['name']        = split(split(dec, ' ')[2], '(')[1];
    method['declaration'] = dec;
    method['description'] = parse_description(comment); 
    method['bottom_description'] = parse_bottom_description(comment); 
    method['params']      = {};
    method['return']      = parse_return(comment);
    method['example']     = parse_example(comment);
    
    -- get params
    local index = 1;
    for match in matches do
        
        method['params'][index] = parse_param(match);

        index = index + 1;
    end


    return method;
end

function parse_header(source)
    local matches = string.gmatch(source, "%/%*%*.-%*%/%s-%\nint .-%(.-%)");
    -- methods: method[]
    local methods = {};

    local index = 1;
    for match in matches do
        methods[index] = parse_comment(match);
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
