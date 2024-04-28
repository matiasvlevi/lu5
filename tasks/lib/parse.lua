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

function parse_descrition(comment)
	local lines = split(comment, '\n');
	local result = {};
	for i=1, #lines do
		-- filter only text
		local m = string.match(lines[i], "%s%*%s[%w ]+")
		if (m ~= nil) then
			table.insert(result, 1, string.sub(m, 4, #m));
		end
	end
	return join(result, '\n');
end

function parse_comment(comment)

    local matches = string.gmatch(comment, "@param %w+ .-%\n");

    -- method
    --  name: string
    --  declaration: string
    --  params: param[]
    local method = {};

    local dec = string.match(comment, 'int %w+%(.*%)') .. ';';

    method['name']        = split(split(dec, ' ')[2], '(')[1];
    method['declaration'] = dec;
    method['description'] = parse_descrition(comment); 
    method['params']      = {};
    
    -- get params
    local index = 0;
    for match in matches do
        method['params'][index] = parse_param(match);
        index = index + 1;
    end

    return method;
end

function parse_header(source)
    local matches = string.gmatch(source, "%/%*%*.-%*%/%s-%\nint%s%w-%(.-%)");
    -- methods: method[]
    local methods = {};

    local index = 1;
    for match in matches do
        methods[index] = parse_comment(match);
        index = index + 1;
    end

    return methods;

end

return {
	description=parse_description,
	header=parse_header,
	param=parse_param,
	comment=parse_comment
}