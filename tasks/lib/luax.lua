

local utils = {
    self_closing_tags = {
        area=0,
        base=0, 
        br=0, 
        col=0, 
        command=0, 
        embed=0, 
        hr=0, 
        img=0, 
        input=0, 
        keygen=0, 
        link=0, 
        meta=0, 
        param=0, 
        source=0, 
        track=0, 
        wbr=0
    };
};

function utils.is_single_closing(elem)
    return (utils.self_closing_tags[elem] ~= nil);
end

function utils.join(list, sep)
    if (sep == nil) then sep = '' end;
    if (#list < 1) then return '' end;
    if (#list == 1) then return list[1]; end;

    local str = list[1];

    for i=2,#list do
        str = str .. sep .. list[i];
    end
    
    return str;
end

function utils.format_props(props)
    -- Format props to string
    local prop_index = 1;
    local prop_count = 0;
    for _,_ in pairs(props) do prop_count = prop_count + 1 end
    local prop_string = (prop_count > 0 and ' ' or '');
    for name, value in pairs(props) do
        local value_type = type(value);
        
        -- Append property
        if (value_type == "boolean") then
            prop_string = prop_string ..  (value and name or '');
        else
            prop_string = prop_string .. 
                name .. '="' .. value .. '"'
        end

         -- Append Space Separator 
        prop_string = prop_string .. 
                ((prop_index < prop_count and value) and ' ' or '');        
        
        prop_index = prop_index + 1
    end
    return prop_string;
end

function utils.children_to_string(children)
    -- Format children to string
    local children_string = '';

    if (type(children) == "table") then
        for i, child in ipairs(children) do
            if (type(child) == "table") then
                -- Add table child & concatenate with luax
                children_string = children_string .. luax('', {}, child)
            else
                -- Add string child
                children_string = children_string .. tostring(child);
            end
        end
    elseif (children ~= nil) then
        -- Set sing children string
        children_string = tostring(children);
    end

    return children_string;
end

---
-- Map data to strings
--
-- @param data The table data to map (either with indicies or keys)
-- @param cb The function which maps the data element to a string (Can be a component)
--
-- @example
-- local names = {
--     'Bob',
--     'Jonh',
--     'Mark'
-- }
-- 
-- local div = luax.map(names, function(name, i)
--     return luax('span', {id=i}, name);
-- end)
--
-- print(div) -- <span id="1">Bob</span><span id="2">Jonh</span><span id="3">Mark</span>
-- @example
---
function utils.map(data, cb)
    local res = {}
    local it = (type(data) == "table" and data[1] ~= nil) and ipairs or pairs;
    for k, value in it(data) do
        res[k] = cb(value, k);
    end
    return res;
end

---
-- Match case for inline logic
--
-- @param key The key to match
-- @param cases A table of strings
--
-- @example
-- -- can be either "banana", "apple", "raisin"
-- local value = "raisin";
-- local div = luax.match(value, {
--      banana=luax('p', 'todo: banana component'),
--      apple=luax('p', 'todo: apple component'),
--      raisin=luax('div', {
--          luax('p', 'This is a raisin')
--      }),
-- })
--
-- print(div) -- <div><p>This is a raisin</p></div>
-- @example
---
function utils.match(key, cases)
    return (cases[key] ~= nil) and cases[key] or (
        (cases["default"] ~= nil) and cases["default"] or ''
    )
end

function utils.split(input, sep)
    local content={}
    for str in string.gmatch(input, "([^"..sep.."]+)") do
        table.insert(content, str);
    end
    return content
end

function utils.filter(list, cb)
    local res = {}
    for i, elem in ipairs(list) do
        if (cb(elem, i)) then
            table.insert(res, elem)
        end
    end
    return res;
end

function utils.merge(a, b)
    local res = a;
    for key, value in pairs(b) do
        res[key] = value;
    end
    return res;
end

function utils.reverse(list)
    local res = {}
    for i, elem in ipairs(list) do
        table.insert(res, 1, elem)
    end
    return res;
end

function utils.insert(host, segment, pos)
    return host:sub(1,pos-1)..segment..host:sub(pos+1)
end

local mt = { 
    __call=function(t, tag, arg1, arg2)
        -- Set arguments
        local props, children;
        if (arg2 == nil and (type(arg1) ~= "table" or arg1[1] ~= nil)) then
            props = {}  ; children = arg1;
        else
            props = arg1; children = arg2;
        end

        return luax(tag, props, children);
    end
};

---
-- A simple JSX-Like String builder
--
-- @param tag - The element's tag name
-- @param props - Properties & attributes
-- @param children - Children elements
--
-- @example
-- local div = luax('div', {
--      luax('h2', 'Hello world!')
-- });
-- print(div) -- <div><h2>Hello world!</h2></div>
-- @example
-- 
-- @example
-- local div = luax('div', {class="container"}, {
--      luax('h2', 'Hello world!'),
--      luax('span', {class="red"}, 'This text is red.')
-- });
-- print(div) -- <div class="container"><h2>Hello world!</h2><span class="red">This text is red.</span></div>
-- @example
---
function luax(tag, props, children)
    -- If tag is empty, return children alone without formating
    -- Commonly known as 'Fragment'
    if (#tag == 0 or string.len(tag) == 0) then
        return utils.children_to_string(children);
    end

    -- Self closing
    local is_single_closing = utils.is_single_closing(tag);
    if (is_single_closing) then
        return '<'..tag .. utils.format_props(props) .. '/>';
    end

    -- With closing tag
    return (
        '<'..tag .. utils.format_props(props) .. '>'
            .. utils.children_to_string(children) ..
        '</' .. tag .. '>'
    )
end;

return setmetatable(utils, mt);