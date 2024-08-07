---
-- A simple JSX-Like String builder
--
-- With 2 arguments:
-- @param tag - The element's tag name
-- @param children - Children elements
--
-- With 3 arguments:
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
function luax(t, tag, arg1, arg2)
    -- Set arguments
    local props = {}
    local children = {}
    if (arg2 == nil and (type(arg1) ~= "table" or arg1[1] ~= nil)) then
        props = {};
        children = arg1;
    else
        props = arg1;
        children = arg2;
    end

    -- Format props to string
    local prop_index = 1;
    local prop_count = 0
    for _,_ in pairs(props) do prop_count = prop_count + 1 end

    local prop_string = (prop_count > 0 and ' ' or '');
    for name, value in pairs(props) do
        prop_string = prop_string .. 
            -- Append property
            name .. '="' .. value .. '"' ..
            -- Space Separator 
            ((prop_index < prop_count) and ' ' or '');

        prop_index = prop_index + 1
    end

    -- Format children to string
    local children_string = '';
    if (type(children) == "table") then
        -- Mutliple children
        for index, child in ipairs(children) do
            children_string = children_string .. tostring(child);
        end
    elseif (children ~= nil) then
        -- Single children value
        children_string = tostring(children);
    end

    -- No root tag
    if (string.len(tag) == 0) then
        -- Return formatted children
        return children_string;
    end

    -- Format Element to string
    return (
        '<'..tag .. prop_string .. (children == nil and '/>' or '>'
            .. children_string .. 
        '</' .. tag .. '>'
    ))
end;

---
-- Detect if is numeric array
-- by checking if first numeric key is set 
---
local function is_array(tbl)
    return type(tbl) ~= "table" and tbl[1] ~= nil;
end

local utils = {};

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
    local res = '';
    local it = is_array(data) and ipairs or pairs;
    for i, value in it(data) do
        res = res .. cb(value, i);
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

function utils.join(list, sep)
    if (sep == nil) then sep = '' end;
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

function utils.split(input, sep)
    local content={}
    for str in string.gmatch(input, "([^"..sep.."]+)") do
        table.insert(content, str);
    end
    return content
end

local mt = { __call=luax };
return setmetatable(utils, mt);